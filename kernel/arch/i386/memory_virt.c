#include <kernel/memory_virt.h>
#include <kernel/memory_phys.h>
#include <drivers/serial.h>

uint32_t page_directory[1024] __attribute__((aligned(4096)));

uint32_t page_table[1024] __attribute__((aligned(4096)));

uint32_t * mem_virt_directory_init() {
    //set each entry to not present
    unsigned int i;
    for(i = 0; i < 1024; i++)
    {
        // This sets the following flags to the pages:
        //   Supervisor: Only kernel-mode can access them
        //   Write Enabled: It can be both read from and written to
        //   Not Present: The page table is not present
        page_directory[i] = 0x00000002;
    }

    mem_virt_table_init();
    page_directory[0] = ((uint32_t)page_table) | 3;
    return page_directory; 
}


void mem_virt_table_init() {
    // holds the physical address where we want to start mapping these pages to.
    // in this case, we want to map these pages to the very beginning of memory.
    unsigned int i;
     
    //we will fill all 1024 entries in the table, mapping 4 megabytes
    for(i = 0; i < 1024; i++)
    {
        // As the address is page aligned, it will always leave 12 bits zeroed.
        // Those bits are used by the attributes ;)
        uint32_t frame_num = mmap_allocate_frame();
        uint32_t frame_ptr = mmap_read(frame_num, MMAP_GET_ADDR);
        char c[32];
        itoa(frame_ptr, c);

        serial_writestring("HERE: ");
        serial_writestring(c);
        page_table[i] = frame_ptr | 3; // attributes: supervisor level, read/write, present.
    }
}
