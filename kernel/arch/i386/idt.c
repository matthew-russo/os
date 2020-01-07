#include <string.h>

#include <kernel/idt.h>

#define NUM_IDT_ENTRIES 256

// asm routine: defined in /kernel/arch/i386/idt_asm.S
extern void idt_flush(uint32_t);

extern void _isr0(void);
extern void _isr1(void);
extern void _isr2(void);
extern void _isr3(void);
extern void _isr4(void);
extern void _isr5(void);
extern void _isr6(void);
extern void _isr7(void);
extern void _isr8(void);
extern void _isr9(void);
extern void _isr10(void);
extern void _isr11(void);
extern void _isr12(void);
extern void _isr13(void);
extern void _isr14(void);
extern void _isr15(void);
extern void _isr16(void);
extern void _isr17(void);
extern void _isr18(void);
extern void _isr19(void);
extern void _isr20(void);
extern void _isr21(void);
extern void _isr22(void);
extern void _isr23(void);
extern void _isr24(void);
extern void _isr25(void);
extern void _isr26(void);
extern void _isr27(void);
extern void _isr28(void);
extern void _isr29(void);
extern void _isr30(void);
extern void _isr31(void);

struct idt_entry idt_entries[NUM_IDT_ENTRIES];
struct idt_ptr idt_ptr;

void idt_encode_entry(uint32_t entry_num,
                      uint32_t base,
                      uint16_t selector,
                      uint8_t  flags)
{
        idt_entries[entry_num].always_zero = 0;
        idt_entries[entry_num].base_lo  = base & 0xFFFF;
        idt_entries[entry_num].base_hi  = (base >> 16) & 0xFFFF;
        idt_entries[entry_num].flags    = flags;
        idt_entries[entry_num].selector = selector;
}

void idt_init(void)
{
        idt_ptr.limit = (sizeof(struct idt_entry) * NUM_IDT_ENTRIES) - 1;
        idt_ptr.base = (uint32_t)&idt_entries;

        memset(&idt_entries, 0, sizeof(struct idt_entry) * NUM_IDT_ENTRIES);

        idt_encode_entry(0,  (uint32_t) _isr0, 0x08, 0x8E);
        idt_encode_entry(1,  (uint32_t) _isr1, 0x08, 0x8E);
        idt_encode_entry(2,  (uint32_t) _isr2, 0x08, 0x8E);
        idt_encode_entry(3,  (uint32_t) _isr3, 0x08, 0x8E);
        idt_encode_entry(4,  (uint32_t) _isr4, 0x08, 0x8E);
        idt_encode_entry(5,  (uint32_t) _isr5, 0x08, 0x8E);
        idt_encode_entry(6,  (uint32_t) _isr6, 0x08, 0x8E);
        idt_encode_entry(7,  (uint32_t) _isr7, 0x08, 0x8E);
        idt_encode_entry(8,  (uint32_t) _isr8, 0x08, 0x8E);
        idt_encode_entry(9,  (uint32_t) _isr9, 0x08, 0x8E);
        idt_encode_entry(10, (uint32_t) _isr10, 0x08, 0x8E);
        idt_encode_entry(11, (uint32_t) _isr11, 0x08, 0x8E);
        idt_encode_entry(12, (uint32_t) _isr12, 0x08, 0x8E);
        idt_encode_entry(13, (uint32_t) _isr13, 0x08, 0x8E);
        idt_encode_entry(14, (uint32_t) _isr14, 0x08, 0x8E);
        idt_encode_entry(15, (uint32_t) _isr15, 0x08, 0x8E);
        idt_encode_entry(16, (uint32_t) _isr16, 0x08, 0x8E);
        idt_encode_entry(17, (uint32_t) _isr17, 0x08, 0x8E);
        idt_encode_entry(18, (uint32_t) _isr18, 0x08, 0x8E);
        idt_encode_entry(19, (uint32_t) _isr19, 0x08, 0x8E);
        idt_encode_entry(20, (uint32_t) _isr20, 0x08, 0x8E);
        idt_encode_entry(21, (uint32_t) _isr21, 0x08, 0x8E);
        idt_encode_entry(22, (uint32_t) _isr22, 0x08, 0x8E);
        idt_encode_entry(23, (uint32_t) _isr23, 0x08, 0x8E);
        idt_encode_entry(24, (uint32_t) _isr24, 0x08, 0x8E);
        idt_encode_entry(25, (uint32_t) _isr25, 0x08, 0x8E);
        idt_encode_entry(26, (uint32_t) _isr26, 0x08, 0x8E);
        idt_encode_entry(27, (uint32_t) _isr27, 0x08, 0x8E);
        idt_encode_entry(28, (uint32_t) _isr28, 0x08, 0x8E);
        idt_encode_entry(29, (uint32_t) _isr29, 0x08, 0x8E);
        idt_encode_entry(30, (uint32_t) _isr30, 0x08, 0x8E);
        idt_encode_entry(31, (uint32_t) _isr31, 0x08, 0x8E);
       
        idt_flush((uint32_t)&idt_ptr);
}

