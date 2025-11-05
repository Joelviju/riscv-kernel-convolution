#ifndef UART_H
#define UART_H

#define UART0_ADDR 0x10000000

void uart_putc(char c);
void uart_puts(const char *s);
void uart_put_hex(unsigned int val);

#endif
