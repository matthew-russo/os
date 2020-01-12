#include <stdlib.h>
#include <stdio.h>
#include <sys/io.h>

#include <kernel/multiboot.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/memory_phys.h>

#include <drivers/serial.h>
 
void kernel_main(uint32_t mboot_magic, void *mboot_header)
{
        terminal_initialize();
        puts("terminal initialized");

        gdt_init();
        puts("gdt initialized");

        idt_init();
        puts("idt initialized");

        memory_phys_init(mboot_magic, mboot_header);
        puts("physical memory initialized");

        uint32_t frame_num = mmap_allocate_frame();
        uint32_t frame_ptr = mmap_read(frame_num, MMAP_GET_ADDR); 

        printf("FRAME_NUM IS: ");
        char c[32];
        itoa(frame_num, c);
        printf(c);
        printf("\n");

        printf("FRAME_PTR IS: ");
        itoa(frame_ptr, c);
        printf(c);
        printf("\n");

        serial_writestring("hello serial world");

        outb(0x64, 0xEE);
}
