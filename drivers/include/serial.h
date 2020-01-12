#ifndef _DRIVER_SERIAL_H
#define _DRIVER_SERIAL_H

#include <stdint.h>

uint8_t serial_read();
void serial_write(uint8_t v);

#endif
