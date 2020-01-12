#include <stdio.h>
#include <stdlib.h>

#include <kernel/multiboot.h>
#include <kernel/memory_phys.h>


multiboot_info_t *verified_multiboot_header;
uint32_t multiboot_reserved_start;
uint32_t multiboot_reserved_end;
uint32_t next_free_frame;

void memory_phys_init(uint32_t mboot_magic, void *mboot_header)
{
    // MULTIBOOT_BOOTLOADER_MAGIC is defined on page 16 of the PDF too
    if (mboot_magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        // If the magic is wrong, we should probably halt the system.
        printf("Error: We weren't booted by a compliant bootloader!\n");
        abort();
    }

    // first, cast the pointer to a multiboot_info_t struct pointer
    multiboot_info_t *multiboot_header = (multiboot_info_t *) mboot_header;

    // The specification states that bit 6 signifies the presence of the memory map
    // We can check the header flags to see if it's there
    if ((multiboot_header->flags & (1<<6)) == 0)
    {
        // The memory map is not present, we should probably halt the system
        printf("Error: No Multiboot memory map was provided!\n");
        abort();
    }

    verified_multiboot_header = multiboot_header;
    multiboot_reserved_start = (uint32_t)multiboot_header;
    multiboot_reserved_end = (uint32_t)(multiboot_header + sizeof(multiboot_info_t));
    next_free_frame = 1;
}

uint32_t mmap_read(uint32_t request, uint8_t mode)
{
    if (request == 0)
    {
        return 0;
    }

    if (mode != MMAP_GET_NUM && mode != MMAP_GET_ADDR)
    {
        return 0;
    }

    uintptr_t cur_mmap_addr = (uintptr_t) verified_multiboot_header->mmap_addr;
    uintptr_t mmap_end_addr = cur_mmap_addr + verified_multiboot_header-> mmap_length;
    uint32_t cur_num = 0;
    while (cur_mmap_addr < mmap_end_addr)
    {
        multiboot_memory_map_t *current_entry = (multiboot_memory_map_t *)cur_mmap_addr;

        uint64_t i;
        uint64_t current_entry_end = current_entry->addr + current_entry->len;
        for (i = current_entry->addr; i + MMAP_PAGE_SIZE < current_entry_end; i += MMAP_PAGE_SIZE)
        {
            if (mode == MMAP_GET_NUM && request >= i && request <= i + MMAP_PAGE_SIZE)
            {
                return cur_num + 1;
            }

            if (current_entry->type == MULTIBOOT_MEMORY_RESERVED)
            {
                if (mode == MMAP_GET_ADDR && cur_num == request)
                {
                    // The address of a chunk in reserved space was requested
                    // Increment the request until it is no longer reserved
                    ++request;
                }

                // Skip to the next chunk until it's no longer reserved
                ++cur_num;
                continue;
            }
            else if (mode == MMAP_GET_ADDR && cur_num == request)
            {
                return i;
            }

            ++cur_num;
        }

        // Increment by the size of the current entry to get to the next one
        cur_mmap_addr += current_entry->size + sizeof(uintptr_t);
    }

    // If no results are found, return 0
    return 0;
}

uint32_t mmap_allocate_frame(void)
{
    // Get the address for the next free frame
    uint32_t cur_addr = mmap_read(next_free_frame, MMAP_GET_ADDR);

    // Verify that the frame is not in the multiboot reserved area
    // If it is, increment the next free frame number and recursively call back.
    if (cur_addr >= multiboot_reserved_start && cur_addr <= multiboot_reserved_end)
    {
        ++next_free_frame;
        return mmap_allocate_frame();
    }

    // Call mmap_read again to get the frame number for our address
    uint32_t cur_num = mmap_read(cur_addr, MMAP_GET_NUM);

    // Update next_free_frame to the next unallocated frame number
    next_free_frame = cur_num + 1;

    // Finally, return the newly allocated frame num
    return cur_num;
}

