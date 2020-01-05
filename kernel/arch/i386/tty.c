#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
 
#include <kernel/tty.h>
 
#include "vga.h"
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
 
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_clearrow(int row)
{
        for (int col = 0; col < VGA_WIDTH; col++)
        {
                const size_t index = row * VGA_WIDTH + col;
                terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
}

void terminal_initialize(void)
{
        terminal_row = 0;
        terminal_column = 0;
        terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        terminal_buffer = VGA_MEMORY;
        for (size_t row = 0; row < VGA_HEIGHT; row++) {
                terminal_clearrow(row);
        }
}
 
void terminal_setcolor(uint8_t color)
{
        terminal_color = color;
}
 
void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
        const size_t index = y * VGA_WIDTH + x;
        terminal_buffer[index] = vga_entry(c, color);
}

void terminal_shiftup()
{
        for (int row = 0; row < VGA_HEIGHT - 1; row++)
        {
                for (int col = 0; col < VGA_WIDTH; col++)
                {
                        const size_t old_index = (row + 1) * VGA_WIDTH + col;
                        const size_t new_index = row * VGA_WIDTH + col;
                        terminal_buffer[new_index] = terminal_buffer[old_index];
                }
        }

        terminal_clearrow(VGA_HEIGHT - 1);
}

void terminal_linefeed()
{
        if (++terminal_row >= VGA_HEIGHT)
        {
                terminal_shiftup();
                --terminal_row;
                terminal_column = 0;
        }
}

bool terminal_handlecontrolchar(char c)
{
        switch (c)
        {
                case '\n':
                        terminal_linefeed();
                        return true;
                default:
                        return false;
        }
}

void terminal_putchar(char c)
{
        if (terminal_handlecontrolchar(c))
        {
              return;
        }

        unsigned char uc = c;
        terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH)
        {
                terminal_linefeed();
        }
}
 
void terminal_write(const char* data, size_t size)
{
        for (size_t i = 0; i < size; i++)
                terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data)
{
        terminal_write(data, strlen(data));
}
