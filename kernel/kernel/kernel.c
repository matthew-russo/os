#include <stdio.h>
 
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
 
void kernel_main(void)
{
        terminal_initialize();
        puts("terminal initialized");
        gdt_init();
        puts("gdt initialized");
        idt_init();
        puts("idt initialized");

        printf("1\n");
        printf("2\n");
        printf("3\n");
        printf("4\n");
        printf("5\n");
        printf("6\n");
        printf("7\n");
        printf("8\n");
        printf("9\n");
        printf("10\n");
        printf("11\n");
        printf("12\n");
        printf("13\n");
        printf("14\n");
        printf("15\n");
        printf("16\n");
        printf("17\n");
        printf("18\n");
        printf("19\n");
        printf("20\n");
        printf("21\n");
        printf("22\n");
        printf("23\n");
        printf("24\n");
        printf("25\n");
        printf("26\n");
        printf("27\n");
        printf("28\n");
        printf("29\n");
        printf("30\n");
}
