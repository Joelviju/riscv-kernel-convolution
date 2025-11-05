#include "uart.h"

void uart_putc(char c) {
    volatile char *uart = (volatile char *)UART0_ADDR;
    *uart = c;
}

void uart_puts(const char *s) {
    while (*s) uart_putc(*s++);
}

void uart_put_hex(unsigned int val) {
    const char hex[] = "0123456789ABCDEF";
    for (int i = 28; i >= 0; i -= 4)
        uart_putc(hex[(val >> i) & 0xF]);
    uart_putc('\n');
}
