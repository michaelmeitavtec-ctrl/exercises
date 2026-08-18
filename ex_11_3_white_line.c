/*
Exercise 11-3: Change Example 11-3 so that it draws a white line across a black
background.
*/

#include <stdio.h>

#define X_SIZE 40 /* size of array in X direction */
#define Y_SIZE 60 /* size of array in Y direction */

/*
 * We use X_SIZE/8 because we pack 8 bits per byte
 */
char graphics[X_SIZE / 8][Y_SIZE];

/**
 * @brief Set a bit at position (x, y) in the graphics array.
 */
#define SET_BIT(x, y) graphics[(x)/8][y] |= (0x80 >> ((x) % 8))

/**
 * @brief Clear (unset) a bit at position (x, y) in the graphics array.
 */
#define CLEAR_BIT(x, y) graphics[(x)/8][y] &= ~(0x80 >> ((x) % 8))

/**
 * @brief Test whether a bit at position (x, y) is set.
 */
#define TEST_BIT(x, y) (graphics[(x)/8][y] & (0x80 >> ((x) % 8)))

void print_graphics(void);
void print_region(int x_start, int x_end, int y_start, int y_end);
void clear_graphics(void);
void clear_graphics_all(void);
void draw_horizontal_line(int y);
void draw_vertical_line(int x);

int main(void)
{
    printf("=== White Line Across Black Background ===\n\n");

    /* Test 1: Horizontal white line across the middle */
    printf("--- Horizontal Line at y=15 (white on black) ---\n");
    clear_graphics();
    draw_horizontal_line(15);
    print_region(0, 40, 10, 25);

    /* Test 2: Vertical white line down the middle */
    printf("\n--- Vertical Line at x=20 (white on black) ---\n");
    clear_graphics();
    draw_vertical_line(20);
    print_region(15, 25, 0, 30);

    /* Test 3: Horizontal and vertical lines (cross) */
    printf("\n--- Horizontal and Vertical Lines (Cross) ---\n");
    clear_graphics();
    draw_horizontal_line(15);
    draw_vertical_line(20);
    print_region(10, 30, 10, 25);

    /* Test 4: Multiple horizontal lines (zebra pattern) */
    printf("\n--- Multiple Horizontal Lines (Zebra Pattern) ---\n");
    clear_graphics();
    for (int y = 5; y < 25; y += 2) {
        draw_horizontal_line(y);
    }
    print_region(0, 40, 0, 30);

    /* Test 5: White background with black line (inverse) */
    printf("\n--- Black Line on White Background (Inverse) ---\n");
    clear_graphics_all();  /* Set all bits to white */
    /* Draw a black horizontal line by clearing bits */
    for (int x = 0; x < X_SIZE; ++x) {
        CLEAR_BIT(x, 15);
    }
    print_region(0, 40, 10, 25);

    return 0;
}

/********************************************************
 * clear_graphics -- Clear all bits (black background)
 ********************************************************/
void clear_graphics(void)
{
    int x, y;

    for (x = 0; x < X_SIZE / 8; ++x) {
        for (y = 0; y < Y_SIZE; ++y) {
            graphics[x][y] = 0;
        }
    }
}

/********************************************************
 * clear_graphics_all -- Set all bits (white background)
 ********************************************************/
void clear_graphics_all(void)
{
    int x, y;

    for (x = 0; x < X_SIZE / 8; ++x) {
        for (y = 0; y < Y_SIZE; ++y) {
            graphics[x][y] = 0xFF;  /* 0xFF = 11111111 in binary */
        }
    }
}

/********************************************************
 * draw_horizontal_line -- Draw a horizontal white line
 *
 * @param y Y-coordinate of the line
 *
 * Draws a white line that spans the entire X width at
 * the specified Y coordinate.
 ********************************************************/
void draw_horizontal_line(int y)
{
    int x;

    if (y < 0 || y >= Y_SIZE) {
        return;  /* Bounds check */
    }

    for (x = 0; x < X_SIZE; ++x) {
        SET_BIT(x, y);
    }
}

/********************************************************
 * draw_vertical_line -- Draw a vertical white line
 *
 * @param x X-coordinate of the line
 *
 * Draws a white line that spans the entire Y height at
 * the specified X coordinate.
 ********************************************************/
void draw_vertical_line(int x)
{
    int y;

    if (x < 0 || x >= X_SIZE) {
        return;  /* Bounds check */
    }

    for (y = 0; y < Y_SIZE; ++y) {
        SET_BIT(x, y);
    }
}

/********************************************************
 * print_graphics -- Prints the entire graphics bit array
 *                   as X's (white/set) and .'s (black/unset).
 ********************************************************/
void print_graphics(void)
{
    print_region(0, X_SIZE, 0, Y_SIZE);
}

/********************************************************
 * print_region -- Prints a rectangular region of the
 *                 graphics bit array as X's (white) and .'s (black).
 *
 * @param x_start Starting X coordinate
 * @param x_end   Ending X coordinate (exclusive)
 * @param y_start Starting Y coordinate
 * @param y_end   Ending Y coordinate (exclusive)
 ********************************************************/
void print_region(int x_start, int x_end, int y_start, int y_end)
{
    int x, y;
    unsigned int bit;

    for (y = y_start; y < y_end; ++y) {
        /* Loop for each byte in the array */
        for (x = x_start; x < x_end; ++x) {
            if (TEST_BIT(x, y)) {
                printf("X");  /* white (bit set) */
            } else {
                printf(".");  /* black (bit unset) */
            }
        }
        printf("\n");
    }
}
