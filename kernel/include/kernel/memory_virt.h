#ifndef _KERNEL_MEMORY_VIRT_H
#define _KERNEL_MEMORY_VIRT_H

#include <stdint.h>

uint32_t * mem_virt_directory_init();

void mem_virt_table_init();

#endif
