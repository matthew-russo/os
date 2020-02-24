#include <stdlib.h>
#include <stdio.h>
#include <sys/io.h>

#include <kernel/multiboot.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/memory_phys.h>

#include <drivers/serial.h>
#include <drivers/pic.h>

void kernel_main(uint32_t mboot_magic, void *mboot_header)
{
    terminal_initialize();
    puts("terminal initialized");

    pic_remap(0x20, 0x28);
    puts("pic remapped");

    gdt_init();
    puts("gdt initialized");

    idt_init();
    puts("idt initialized");

    asm("int $3");

    // memory_phys_init(mboot_magic, mboot_header);
    // puts("physical memory initialized");

    // uint32_t frame_num = mmap_allocate_frame();
    // uint32_t frame_ptr = mmap_read(frame_num, MMAP_GET_ADDR); 

    serial_writestring("hello serial world");

    outb(0x64, 0xEE);
}
