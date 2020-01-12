#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <sys/io.h>
#include <drivers/serial.h>

#define SERIAL_DATA_REGISTER         0x3F8
#define SERIAL_BAUD_DIVISOR_LSB      0x3F8
#define SERIAL_INTERRUPT_ENABLE_REGISTER SERIAL_DATA_REGISTER + 1
#define SERIAL_BAUD_DIVISOR_MSB      SERIAL_DATA_REGISTER + 1
#define SERIAL_INTERRUPT_ID_FIFO_CONTROL SERIAL_DATA_REGISTER + 2
#define SERIAL_LINE_CONTROL_REGISTER     SERIAL_DATA_REGISTER + 3
#define SERIAL_MODEM_CONTROL_REGISTER    SERIAL_DATA_REGISTER + 4
#define SERIAL_LINE_STATUS_REGISTER      SERIAL_DATA_REGISTER + 5
#define SERIAL_MODEM_STATUS_REGISTER     SERIAL_DATA_REGISTER + 6
#define SERIAL_SCRATCH_REGISTER      SERIAL_DATA_REGISTER + 7

// Interrupt enable register
// 
// To communicate with a serial port in interrupt mode, the interrupt-enable-register (see table above) must be set correctly. To determine which interrupts should be enabled, a value with the following bits (0 = disabled, 1 = enabled) must be written to the interrupt-enable-register:
const uint8_t SERIAL_INTER_DATA_AVAILABLE    = 0b0001;
const uint8_t SERIAL_INTER_TRANSMITTER_EMPTY = 0b0010;
const uint8_t SERIAL_INTER_BREAK         = 0b0100;
const uint8_t SERIAL_INTER_STATUS_CHANGE     = 0b1000;

// Line status register
// The line status register is useful to check for errors and enable polling.
const uint8_t SERIAL_LINE_DATA_READY      = 0b00000001;
const uint8_t SERIAL_LINE_OVERRUN         = 0b00000010;
const uint8_t SERIAL_LINE_PARITY          = 0b00000100;
const uint8_t SERIAL_LINE_FRAMING         = 0b00001000;
const uint8_t SERIAL_LINE_BREAK           = 0b00010000;
const uint8_t SERIAL_LINE_TRANS_HOLDING_EMPTY = 0b00100000;
const uint8_t SERIAL_LINE_TRANS_EMPTY     = 0b01000000;
const uint8_t SERIAL_LINE_IMPENDING       = 0b10000000;

void serial_init(void) {
    outb(SERIAL_INTERRUPT_ENABLE_REGISTER, 0x00); // Disable all interrupts
    outb(SERIAL_LINE_CONTROL_REGISTER, 0x80);     // Enable DLAB (set baud rate divisor)
    outb(SERIAL_BAUD_DIVISOR_LSB, 0x03);      // Set divisor to 3 (lo byte) 38400 baud
    outb(SERIAL_BAUD_DIVISOR_MSB, 0x00);      //          (hi byte)
    outb(SERIAL_LINE_CONTROL_REGISTER, 0x03);     // 8 bits, no parity, one stop bit
    outb(SERIAL_INTERRUPT_ID_FIFO_CONTROL, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    outb(SERIAL_MODEM_CONTROL_REGISTER, 0x0B);    // IRQs enabled, RTS/DSR set
}

bool serial_received(void)
{
    return inb(SERIAL_LINE_STATUS_REGISTER) & SERIAL_LINE_DATA_READY;
}

uint8_t serial_read(void)
{
    while (!serial_received());
    return inb(SERIAL_DATA_REGISTER);
}

bool is_transmit_empty(void)
{
    return inb(SERIAL_LINE_STATUS_REGISTER) & SERIAL_LINE_TRANS_HOLDING_EMPTY;
}

void serial_writechar(uint8_t b)
{
    while (!is_transmit_empty());
    outb(SERIAL_DATA_REGISTER, b);
}

void serial_writestring(char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        serial_writechar(str[i]);
    }
}
