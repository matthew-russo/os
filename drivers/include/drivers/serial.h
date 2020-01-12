#ifndef _DRIVER_SERIAL_H
#define _DRIVER_SERIAL_H

#include <stdint.h>

uint8_t serial_read(void);
void serial_writechar(uint8_t v);
void serial_writestring(char *str);

#endif
