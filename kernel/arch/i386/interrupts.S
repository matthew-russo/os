.section .text
.align 4

.extern isr_handler
.type isr_handler, @function

# This is our common ISR stub. It saves the processor state, sets
# up for kernel mode segments, calls the C-level fault handler,
# and finally restores the stack frame.
isr_common:
   pusha                    # Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov %ax, %ds               # Lower 16-bits of eax = ds.
   push %eax                 # save the data segment descriptor

   mov %ax, 0x10  # load the kernel data segment descriptor
   mov %ds, %ax
   mov %es, %ax
   mov %fs, %ax
   mov %gs, %ax

   call isr_handler

   pop %eax        # reload the original data segment descriptor
   mov %ds, %ax
   mov %es, %ax
   mov %fs, %ax
   mov %gs, %ax

   popa                     # Pops edi,esi,ebp...
   add %esp, 8     # Cleans up the pushed error code and pushed ISR number
   sti
   iret           # pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

.global _isr0
.type _isr0, @function
_isr0:
    cli
    push $0
    push $0
    jmp isr_common

.global _isr1
.type _isr1, @function
_isr1:
    cli
    push $0
    push $1
    jmp isr_common

.global _isr2
.type _isr2, @function
_isr2:
    cli
    push $0
    push $2
    jmp isr_common

.global _isr3
.type _isr3, @function
_isr3:
    cli
    push $0
    push $3
    jmp isr_common

.global _isr4
.type _isr4, @function
_isr4:
    cli
    push $0
    push $4
    jmp isr_common

.global _isr5
.type _isr5, @function
_isr5:
    cli
    push $0
    push $5
    jmp isr_common

.global _isr6
.type _isr6, @function
_isr6:
    cli
    push $0
    push $6
    jmp isr_common

.global _isr7
.type _isr7, @function
_isr7:
    cli
    push $0
    push $7
    jmp isr_common

.global _isr8
.type _isr8, @function
_isr8:
    cli
    push $8
    jmp isr_common

.global _isr9
.type _isr9, @function
_isr9:
    cli
    push $0
    push $9
    jmp isr_common

.global _isr10
.type _isr10, @function
_isr10:
    cli
    push $10
    jmp isr_common

.global _isr11
.type _isr11, @function
_isr11:
    cli
    push $11
    jmp isr_common

.global _isr12
.type _isr12, @function
_isr12:
    cli
    push $12
    jmp isr_common

.global _isr13
.type _isr13, @function
_isr13:
    cli
    push $13
    jmp isr_common

.global _isr14
.type _isr14, @function
_isr14:
    cli
    push $14
    jmp isr_common

.global _isr15
.type _isr15, @function
_isr15:
    cli
    push $0
    push $15
    jmp isr_common

.global _isr16
.type _isr16, @function
_isr16:
    cli
    push $0
    push $16
    jmp isr_common

.global _isr17
.type _isr17, @function
_isr17:
    cli
    push $0
    push $17
    jmp isr_common

.global _isr18
.type _isr18, @function
_isr18:
    cli
    push $0
    push $18
    jmp isr_common

.global _isr19
.type _isr19, @function
_isr19:
    cli
    push $0
    push $19
    jmp isr_common

.global _isr20
.type _isr20, @function
_isr20:
    cli
    push $0
    push $20
    jmp isr_common

.global _isr21
.type _isr21, @function
_isr21:
    cli
    push $0
    push $21
    jmp isr_common

.global _isr22
.type _isr22, @function
_isr22:
    cli
    push $0
    push $22
    jmp isr_common

.global _isr23
.type _isr23, @function
_isr23:
    cli
    push $0
    push $23
    jmp isr_common

.global _isr24
.type _isr24, @function
_isr24:
    cli
    push $0
    push $24
    jmp isr_common

.global _isr25
.type _isr25, @function
_isr25:
    cli
    push $0
    push $25
    jmp isr_common

.global _isr26
.type _isr26, @function
_isr26:
    cli
    push $0
    push $26
    jmp isr_common

.global _isr27
.type _isr27, @function
_isr27:
    cli
    push $0
    push $27
    jmp isr_common

.global _isr28
.type _isr28, @function
_isr28:
    cli
    push $0
    push $28
    jmp isr_common

.global _isr29
.type _isr29, @function
_isr29:
    cli
    push $0
    push $29
    jmp isr_common

.global _isr30
.type _isr30, @function
_isr30:
    cli
    push $0
    push $30
    jmp isr_common

.global _isr31
.type _isr31, @function
_isr31:
    cli
    push $0
    push $31
    jmp isr_common

