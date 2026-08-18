/*
Exercise 11-2: Write a program to draw a 10-by-10 bitmapped square. You can
borrow the code from Example 11-3 to print the results.
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
void draw_filled_square(int x_start, int y_start, int size);
void draw_hollow_square(int x_start, int y_start, int size);

int main(void)
{
    printf("=== 10x10 Bitmapped Square ===\n\n");

    /* Test 1: Filled 10x10 square at origin */
    printf("--- Filled 10x10 Square at (0, 0) ---\n");
    clear_graphics();
    draw_filled_square(0, 0, 10);
    print_region(0, 15, 0, 15);

    /* Test 2: Filled 10x10 square at different position */
    printf("\n--- Filled 10x10 Square at (15, 10) ---\n");
    clear_graphics();
    draw_filled_square(15, 10, 10);
    print_region(10, 30, 8, 23);

    /* Test 3: Hollow 10x10 square */
    printf("\n--- Hollow 10x10 Square at (5, 5) ---\n");
    clear_graphics();
    draw_hollow_square(5, 5, 10);
    print_region(0, 20, 0, 20);

    /* Test 4: Multiple squares */
    printf("\n--- Two Overlapping Squares ---\n");
    clear_graphics();
    draw_filled_square(0, 0, 10);
    draw_hollow_square(5, 5, 10);
    print_region(0, 20, 0, 20);

    return 0;
}

/********************************************************
 * clear_graphics -- Clear all bits in the graphics array
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
 * draw_filled_square -- Draw a filled square
 *
 * @param x_start Starting X coordinate
 * @param y_start Starting Y coordinate
 * @param size    Width and height of the square
 ********************************************************/
void draw_filled_square(int x_start, int y_start, int size)
{
    int x, y;

    for (x = x_start; x < x_start + size; ++x) {
        for (y = y_start; y < y_start + size; ++y) {
            /* Bounds checking to avoid writing outside the array */
            if (x >= 0 && x < X_SIZE && y >= 0 && y < Y_SIZE) {
                SET_BIT(x, y);
            }
        }
    }
}

/********************************************************
 * draw_hollow_square -- Draw the outline of a square
 *
 * @param x_start Starting X coordinate
 * @param y_start Starting Y coordinate
 * @param size    Width and height of the square
 ********************************************************/
void draw_hollow_square(int x_start, int y_start, int size)
{
    int i;

    /* Top and bottom edges */
    for (i = 0; i < size; ++i) {
        int x = x_start + i;
        int y_top = y_start;
        int y_bottom = y_start + size - 1;

        if (x >= 0 && x < X_SIZE) {
            if (y_top >= 0 && y_top < Y_SIZE) {
                SET_BIT(x, y_top);
            }
            if (y_bottom >= 0 && y_bottom < Y_SIZE) {
                SET_BIT(x, y_bottom);
            }
        }
    }

    /* Left and right edges */
    for (i = 0; i < size; ++i) {
        int y = y_start + i;
        int x_left = x_start;
        int x_right = x_start + size - 1;

        if (y >= 0 && y < Y_SIZE) {
            if (x_left >= 0 && x_left < X_SIZE) {
                SET_BIT(x_left, y);
            }
            if (x_right >= 0 && x_right < X_SIZE) {
                SET_BIT(x_right, y);
            }
        }
    }
}

/********************************************************
 * print_graphics -- Prints the entire graphics bit array
 *                   as X's and .'s.
 ********************************************************/
void print_graphics(void)
{
    print_region(0, X_SIZE, 0, Y_SIZE);
}

/********************************************************
 * print_region -- Prints a rectangular region of the
 *                 graphics bit array as X's and .'s.
 *
 * @param x_start Starting X coordinate
 * @param x_end   Ending X coordinate (exclusive)
 * @param y_start Starting Y coordinate
 * @param y_end   Ending Y coordinate (exclusive)
 ********************************************************/
void print_region(int x_start, int x_end, int y_start, int y_end)
{
    int x, y;

    for (y = y_start; y < y_end; ++y) {
        for (x = x_start; x < x_end; ++x) {
            if (TEST_BIT(x, y)) {
                printf("X");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}
