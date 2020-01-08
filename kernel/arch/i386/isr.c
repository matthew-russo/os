#include <stdlib.h>
#include <stdio.h>
#include <sys/io.h>

#include <kernel/isr.h>

void isr_handler(struct registers regs)
{
        // Send an EOI (end of interrupt) signal to the PICs.
        // If this interrupt involved the slave.
        if (regs.int_no >= 40) {
            // Send reset signal to slave.
            _outb(0xA0, 0x20);
        }
        // Send reset signal to master.
        _outb(0x20, 0x20);

        char s[32]; 
        itoa(regs.int_no, s);
        printf("recieved interrupt: ");
        printf(s);
        printf("\n");
} 
