#include <stdio.h>
#include "processing.h"  
#include "draw.h"
 // includes draw.h and otter.h indirectly

// -------------------------------------------------------------------
// Dummy implementation of draw_dot() for desktop testing.
// Matches the declaration from draw.h:
//     void draw_dot(unsigned int offset, unsigned char RGB);
// -------------------------------------------------------------------
void draw_dot(unsigned int offset, unsigned char RGB)
{
    // (void) is used to silence "unused parameter" warnings
    (void)offset;
    (void)RGB;

    // Optional: Print debug info to see what’s being "drawn"
    // printf("draw_dot() called: offset=%u, RGB=0x%02X\n", offset, RGB);
}

// -------------------------------------------------------------------
// Main test program
// -------------------------------------------------------------------
int main(void)
{
    printf("Running processing tests...\n");

    // X_RES and Y_RES are already defined in otter.h (200x200)
    // RGB_332_type is defined in your processing headers.
    RGB_332_type image[X_RES * Y_RES];

    // Fill the image array with a test pattern
    for (int i = 0; i < X_RES * Y_RES; i++) {
        image[i] = (unsigned char)(i % 256);  // Simple repeating pattern
    }

    // Test the grayscale conversion function
    printf("Applying grayscale filter...\n");
    grayscale(image, 1);

    // (Optional) test other filters when ready:
    // shift_color(image, 1, -1, 0);
    // sobel(image, 3);
    // convolve(image, kernel, divisor);

    printf("Processing complete.\n");
    return 0;
}
