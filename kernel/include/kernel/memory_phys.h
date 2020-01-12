#ifndef _KERNEL_MEMORY_PHYS_H
#define _KERNEL_MEMORY_PHYS_H

#define MMAP_GET_NUM  0
#define MMAP_GET_ADDR 1
#define MMAP_PAGE_SIZE     4096

#include <stdint.h>

#include <kernel/multiboot.h>

void memory_phys_init(uint32_t mboot_magic, void *mboot_header);


/**
 * A function to iterate through the multiboot memory map.
 * If `mode` is set to MMAP_GET_NUM, it will return the frame number for the
 * frame at address `request`.
 * If `mode` is set to MMAP_GET_ADDR, it will return the starting address for
 * the frame number `request`.
 */
uint32_t mmap_read(uint32_t request, uint8_t mode);

/**
 * Allocate the next free frame and return it's frame number
 */
uint32_t mmap_allocate_frame(void);

#endif
