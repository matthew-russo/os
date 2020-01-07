#include <kernel/gdt.h>

#define NUM_GDT_ENTRIES 5

// asm routine: defined in /kernel/arch/i386/gdt.S
extern void gdt_flush(uintptr_t);

struct gdt_entry gdt_entries[NUM_GDT_ENTRIES];
struct gdt_ptr gdt_ptr;

void gdt_init(void)
{
        gdt_ptr.limit = (sizeof(struct gdt_entry) * NUM_GDT_ENTRIES) - 1;
        gdt_ptr.base = (uint32_t)&gdt_entries;

        gdt_encode_entry(0, 0, 0, 0, 0);
        gdt_encode_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
        gdt_encode_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
        gdt_encode_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
        gdt_encode_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

        gdt_flush((uintptr_t)&gdt_ptr);
}

void gdt_encode_entry(uint32_t entry_num,
                      uint32_t base,
                      uint32_t limit,
                      uint8_t  access,
                      uint8_t  granularity)
{
        gdt_entries[entry_num].base_lo = base & 0xFFFF;
        gdt_entries[entry_num].base_mid = (base >> 16) & 0xFF;
        gdt_entries[entry_num].base_hi = (base >> 24) & 0xFF;
        gdt_entries[entry_num].limit_lo = limit & 0xFFFF;
        gdt_entries[entry_num].granularity = (limit >> 16) & 0x0F;
        gdt_entries[entry_num].granularity |= granularity & 0xF0;
        gdt_entries[entry_num].access = access;
}

