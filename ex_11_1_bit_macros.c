/* 
Exercise 11-1: Write a set of parameterized macros, clear_bit and test_bit, to
go with the set_bit operation defined in Example 11-3. Write a main program to
test these macros.
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
 *
 * Sets the bit to 1 using bitwise OR.
 */

#define SET_BIT(x, y) graphics[(x)/8][y] |= (0x80 >> ((x) % 8))

/**
 * @brief Clear (unset) a bit at position (x, y) in the graphics array.
 *
 * Clears the bit to 0 by AND-ing with the bitwise complement of the mask.
 * ~(0x80 >> ((x)%8)) produces a mask with all bits set except the target bit.
 */
#define CLEAR_BIT(x, y) graphics[(x)/8][y] &= ~(0x80 >> ((x) % 8))

/**
 * @brief Test whether a bit at position (x, y) is set.
 *
 * Returns non-zero (true) if the bit is 1, zero (false) if the bit is 0.
 * The result can be used directly in an if() condition.
 */

#define TEST_BIT(x, y) (graphics[(x)/8][y] & (0x80 >> ((x) % 8)))

void print_graphics(void);
void print_region(int x_start, int x_end, int y_start, int y_end);

int main(void)
{
    printf("=== Bit Manipulation Test Suite ===\n\n");

    /* Test 1: Set a simple pattern and verify */
    printf("--- Test 1: Set diagonal line and verify with TEST_BIT ---\n");
    for (int i = 0; i < 10; ++i) {
        SET_BIT(i, i);
    }

    int all_set = 1;
    for (int i = 0; i < 10; ++i) {
        if (!TEST_BIT(i, i)) {
            printf("FAIL: Bit (%d, %d) should be set but isn't.\n", i, i);
            all_set = 0;
        }
    }
    if (all_set) {
        printf("PASS: All diagonal bits (0..9, 0..9) are correctly set.\n");
    }

    /* Verify some off-diagonal bits are NOT set */

    int none_set = 1;
    for (int i = 0; i < 5; ++i) {
        if (TEST_BIT(i, i + 1)) {  /* off-diagonal */
            printf("FAIL: Bit (%d, %d) should NOT be set but is.\n", i, i + 1);
            none_set = 0;
        }
    }
    if (none_set) {
        printf("PASS: Off-diagonal bits correctly remain unset.\n");
    }

    print_region(0, 10, 0, 10);

    /* Test 2: Set a pattern, then clear specific bits */
    printf("\n--- Test 2: Set a block, then clear some bits ---\n");

    /* Clear the diagonal first */
    for (int i = 0; i < 10; ++i) {
        CLEAR_BIT(i, i);
    }

    /* Set a 5x5 block at (0,0) to (4,4) */
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 5; ++y) {
            SET_BIT(x, y);
        }
    }

    printf("5x5 block at (0,0):\n");
    print_region(0, 5, 0, 5);

    /* Clear a cross through the middle */
    for (int i = 0; i < 5; ++i) {
        CLEAR_BIT(i, 2);  /* middle row */
        CLEAR_BIT(2, i);  /* middle column */
    }

    printf("After clearing a cross:\n");
    print_region(0, 5, 0, 5);

    /* Test 3: Toggle bits (set then clear) */
    printf("\n--- Test 3: Verify toggling works ---\n");

    CLEAR_BIT(0, 0);  /* Should already be cleared from the cross */
    if (!TEST_BIT(0, 0)) {
        printf("PASS: Bit (0,0) is cleared.\n");
    } else {
        printf("FAIL: Bit (0,0) should be cleared.\n");
    }

    SET_BIT(0, 0);
    if (TEST_BIT(0, 0)) {
        printf("PASS: Bit (0,0) is set.\n");
    } else {
        printf("FAIL: Bit (0,0) should be set.\n");
    }

    CLEAR_BIT(0, 0);
    if (!TEST_BIT(0, 0)) {
        printf("PASS: Bit (0,0) is cleared again.\n");
    } else {
        printf("FAIL: Bit (0,0) should be cleared.\n");
    }

    /* Test 4: Boundary conditions */
    printf("\n--- Test 4: Boundary conditions ---\n");

    /* Set and test corner bits */
    SET_BIT(0, 0);
    SET_BIT(X_SIZE - 1, 0);
    SET_BIT(0, Y_SIZE - 1);
    SET_BIT(X_SIZE - 1, Y_SIZE - 1);

    if (TEST_BIT(0, 0) && TEST_BIT(X_SIZE - 1, 0) &&
        TEST_BIT(0, Y_SIZE - 1) && TEST_BIT(X_SIZE - 1, Y_SIZE - 1)) {
        printf("PASS: All four corner bits can be set and tested.\n");
    } else {
        printf("FAIL: Some corner bits failed.\n");
    }

    /* Clear them all */
    CLEAR_BIT(0, 0);
    CLEAR_BIT(X_SIZE - 1, 0);
    CLEAR_BIT(0, Y_SIZE - 1);
    CLEAR_BIT(X_SIZE - 1, Y_SIZE - 1);

    if (!TEST_BIT(0, 0) && !TEST_BIT(X_SIZE - 1, 0) &&
        !TEST_BIT(0, Y_SIZE - 1) && !TEST_BIT(X_SIZE - 1, Y_SIZE - 1)) {
        printf("PASS: All four corner bits can be cleared and tested.\n");
    } else {
        printf("FAIL: Some corner bits failed to clear.\n");
    }

    printf("\n=== Tests Complete ===\n");

    return 0;
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
    unsigned int bit;

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
  
