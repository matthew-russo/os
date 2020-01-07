#include <stdlib.h>
#include <stdio.h>

#include <kernel/isr.h>

void isr_handler(struct registers regs)
{
        printf("recieved interrupt: ");
        char s[32]; 
        itoa(regs.int_no, s);
        printf(s);
        printf("\n");
} 
