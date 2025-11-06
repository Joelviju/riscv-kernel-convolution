#ifndef DRAW_H
#define DRAW_H

#include "otter.h"   // <-- coord_type and RGB_332_type already come from here

// We DO NOT redefine coord_type or RGB_332_type here.
// otter.h already has:
//   typedef unsigned char  RGB_332_type;
//   typedef unsigned int   coord_type;

// MMIO addresses (already defined in otter.h, but keep safe fallback)
#ifndef VGA_ADDR
#define VGA_ADDR (0x11100000)
#endif
#ifndef LEDS_ADDR
#define LEDS_ADDR (0x11080000)
#endif
#ifndef SWITCHES_ADDR
#define SWITCHES_ADDR (0x11000000)
#endif


/* ============================
   DRAW_DOT MACRO
   ============================ */

#ifndef MULTICYCLE

// Function prototype for FPGA mode
void draw_dot(coord_type offset, RGB_332_type RGB);

#ifdef QEMU_MODE
    // QEMU: skip hardware writes
    #define DRAW_DOT(RGB) ((void)(RGB))
#else
    // FPGA: real pixel write
    #define DRAW_DOT(RGB) draw_dot(offset, (RGB))
#endif

#else // MULTICYCLE MODE

void draw_dot(int col, int row, unsigned char RGB);

#ifdef QEMU_MODE
    #define DRAW_DOT(RGB) ((void)(RGB))
#else
    #define DRAW_DOT(RGB) draw_dot(col, row, (RGB))
#endif

#endif // MULTICYCLE

#endif // DRAW_H

