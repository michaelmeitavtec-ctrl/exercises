/*
Now to specify the bit itself. A bit index of zero indicates the left-most bit or the bit
represented by 1000 00002 or 0x80. A bit index of 1 indicates the
next-to-the-left-most bit 0100 0000 2 or 0x80 >> 1. So the bit we want is given by
the expression:
bit = 0x80 >> bit_index;
The full algorithm looks like:
byte_y = y;
byte_x = x / 8;
bit_index = x % 8;
bit = 0x80 >> bit_index;
graphics[byte_x][byte_y] |= bit;
*/
#include <stdint.h>

#define DISPLAY_WIDTH  128
#define DISPLAY_HEIGHT 64

#define BUFFER_WIDTH_BYTES (DISPLAY_WIDTH / 8)

// Framebuffer organized as [y_row][x_byte]
uint8_t graphics[DISPLAY_HEIGHT][BUFFER_WIDTH_BYTES];

void draw_pixel(uint16_t x, uint16_t y) {
    // 1. Boundary check to prevent array out-of-bounds access
    if (x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT) {
        return;
    }

    // 2. Fast coordinate calculation
    uint16_t byte_x = x >> 3;         // x / 8
    uint8_t  bit_index = x & 0x07;    // x % 8
    uint8_t  bit_mask = 0x80 >> bit_index; // MSB first

    // 3. Set pixel
    graphics[y][byte_x] |= bit_mask;
}

void clear_pixel(uint16_t x, uint16_t y) {
    if (x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT) {
        return;
    }

    uint16_t byte_x = x >> 3;
    uint8_t  bit_index = x & 0x07;
    uint8_t  bit_mask = 0x80 >> bit_index;

    // Clear bit using bitwise AND with inverted mask
    graphics[y][byte_x] &= (uint8_t)~bit_mask;
}
