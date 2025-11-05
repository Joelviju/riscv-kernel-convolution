#include "draw.h"
#include "processing.h"
#include "uart.h"   // ✅ Added for QEMU UART output


#ifndef MULTICYCLE
void draw_dot(coord_type offset, RGB_332_type RGB)
{
    // Write pixel to VGA memory (works only on FPGA)
    ((RGB_332_type *)VGA_ADDR)[offset] = RGB;

    // ✅ Limit debug output to avoid flooding QEMU
    if (offset % 500 == 0) {
        uart_puts("Pixel #");
        uart_put_hex(offset);
        uart_puts(" RGB=");
        uart_put_hex(RGB);
        uart_puts("\n");
    }
}
#endif

#ifdef MULTICYCLE
void draw_dot(int col, int row, unsigned char RGB)
{
    unsigned int *vgaAddr   = (unsigned int *)0x11100000;
    unsigned char *vgaColor = (unsigned char *)0x11140000;

    int address = col & 0b111111111;
    int temp    = row & 0b011111111;
    temp = temp << 9;
    address = address | temp;
    *(vgaAddr)  = address;
    *(vgaColor) = RGB;

    // ✅ Limited UART debug (for QEMU visibility)
    if ((col + row) % 100 == 0) {
        uart_puts("MC Pixel [");
        uart_put_hex(col);
        uart_puts(",");
        uart_put_hex(row);
        uart_puts("] RGB=");
        uart_put_hex(RGB);
        uart_puts("\n");
    }
}
#endif

// ✅ Draws an image pixel by pixel
void draw_image(RGB_332_type *image)
{
    uart_puts("Drawing image...\n");

    int offset = 0;
    for (int row = 0; row < Y_RES; row++)
    {
        for (int col = 0; col < X_RES; col++)
        {
            RGB_332_type RGB = image[offset];
            DRAW_DOT(RGB);
            offset++;
        }
    }

    uart_puts("Image draw complete!\n");
}

// ✅ Benchmark routine for Sobel filter (hardware switch dependent)
void sobel_bench(RGB_332_type *image)
{
    uart_puts("Starting Sobel benchmark...\n");

    int sw_val = 1;
    *((int *)LEDS_ADDR) = 0;

    while (sw_val != 0)
        sw_val = *((int *)SWITCHES_ADDR);

    *((int *)LEDS_ADDR) = 1;
    sobel(image, 0);
    *((int *)LEDS_ADDR) = 0;

    while (sw_val == 0)
        sw_val = *((int *)SWITCHES_ADDR);

    uart_puts("Sobel benchmark complete.\n");
}

// ✅ Main image processing entry point
void run_img_proc(RGB_332_type *image)
{
    uart_puts("Running image processing pipeline...\n");

    draw_image(image);

#ifdef BENCH
    uart_puts("BENCH mode active: Running Sobel...\n");
    sobel_bench(image);
#endif

    uart_puts("Image processing complete.\n");
}
