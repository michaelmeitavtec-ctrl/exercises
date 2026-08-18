/*
Exercise 11-6: Write a program that will take the bits in a number and shift them
to the left end. For example, 01010110 (binary) would become 11110000 (binary).
*/
#include <stdio.h>
#include <limits.h>

/**
 * @brief Count the number of bits set in an unsigned integer.
 *
 * Uses Kernighan's algorithm for efficiency.
 */
int count_bits(unsigned int value)
{
    int count = 0;

    while (value != 0) {
        value &= (value - 1);  /* Clear the rightmost set bit */
        count++;
    }

    return count;
}

/**
 * @brief Shift bits to the left end of an unsigned integer.
 *
 * Takes all the set bits in the input and moves them to the most
 * significant positions, filling the right end with zeros.
 *
 * Algorithm:
 *   1. Count the number of set bits (let's call it N)
 *   2. Create a mask with N ones: ((1U << N) - 1)
 *   3. Shift that mask to the left end: mask << (bit_width - N)
 *
 * Example with 8-bit number:
 *   Input:  01010110 (5 bits set)
 *   Count:  5
 *   Mask:   00011111 (5 ones on right)
 *   Shift:  00011111 << 3 = 11111000
 *   Output: 11111000
 *
 * @param value The unsigned integer to process.
 * @param bit_width The number of bits in the integer (typically 32 or 64).
 * @return The value with all bits shifted to the left end.
 */
unsigned int shift_bits_to_left(unsigned int value, int bit_width)
{
    int bit_count = count_bits(value);

    if (bit_count == 0) {
        return 0;  /* No bits set, result is 0 */
    }

    if (bit_count == bit_width) {
        return value;  /* All bits set, no change */
    }

    /* Create a mask with bit_count ones: (1U << bit_count) - 1 */
    /* Shift it to the left end: mask << (bit_width - bit_count) */
    unsigned int mask = (1U << bit_count) - 1;
    return mask << (bit_width - bit_count);
}

/* ---------------------- Helper Functions ---------------------- */

/**
 * @brief Print an unsigned integer in binary with separators.
 */
void print_binary(unsigned int value, int bit_width)
{
    for (int i = bit_width - 1; i >= 0; --i) {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0 && i > 0) printf("_");
    }
}

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_shift_bits(const char *label, unsigned char value,
                     unsigned char expected)
{
    unsigned char result = (unsigned char)shift_bits_to_left((unsigned int)value, 8);
    tests_run++;

    int pass = (result == expected);

    printf("%-35s\n", label);
    printf("  Input:    ");
    print_binary(value, 8);
    printf(" (%d set bits)\n", count_bits(value));

    printf("  Output:   ");
    print_binary(result, 8);
    printf("\n");

    printf("  Expected: ");
    print_binary(expected, 8);
    printf("\n");

    printf("  Decimal:  %3d -> %3d (Expected: %3d) -> %s\n",
           value, result, expected, pass ? "PASS" : "FAIL");
    printf("\n");

    if (pass) {
        tests_passed++;
    }
}

void test_shift_bits_32(const char *label, unsigned int value,
                        unsigned int expected)
{
    unsigned int result = shift_bits_to_left(value, 32);
    tests_run++;

    int pass = (result == expected);

    printf("%-40s\n", label);
    printf("  Input:    0x%08X (", value);
    print_binary(value, 32);
    printf(")\n  Set bits: %d\n", count_bits(value));

    printf("  Output:   0x%08X (", result);
    print_binary(result, 32);
    printf(")\n");

    printf("  Expected: 0x%08X (", expected);
    print_binary(expected, 32);
    printf(")\n");

    printf("  Result: %s\n\n", pass ? "PASS" : "FAIL");

    if (pass) {
        tests_passed++;
    }
}

int main(void)
{
    printf("=== Shift Bits to the Left End ===\n\n");

    /* Test 1: Example from the exercise (8-bit) */
    printf("--- Example from Exercise (8-bit) ---\n");
    test_shift_bits("01010110 -> 11110000", 0x56, 0xF0);

    /* Test 2: Basic 8-bit cases */
    printf("--- Basic 8-bit Cases ---\n");
    test_shift_bits("Zero (no bits set)", 0x00, 0x00);
    test_shift_bits("Single bit (LSB)", 0x01, 0x80);
    test_shift_bits("Single bit (MSB)", 0x80, 0x80);
    test_shift_bits("Two bits scattered", 0x05, 0xC0);  /* 00000101 -> 11000000 */
    test_shift_bits("All bits set", 0xFF, 0xFF);
    test_shift_bits("Alternating pattern", 0xAA, 0xF0);  /* 10101010 -> 11110000 (4 bits) */

    /* Test 3: Different patterns */
    printf("--- Various Bit Patterns ---\n");
    test_shift_bits("Lower nibble all set", 0x0F, 0xF0);
    test_shift_bits("Upper nibble all set", 0xF0, 0xF0);
    test_shift_bits("Every other bit", 0x55, 0xF0);  /* 01010101 -> 11110000 (4 bits) */
    test_shift_bits("3 bits set", 0x07, 0xE0);       /* 00000111 -> 11100000 */
    test_shift_bits("3 bits scattered", 0x49, 0xE0); /* 01001001 -> 11100000 */

    /* Test 4: 32-bit cases */
    printf("--- 32-bit Cases ---\n");
    test_shift_bits_32("No bits set", 0x00000000, 0x00000000);
    test_shift_bits_32("Single bit (LSB)", 0x00000001, 0x80000000);
    test_shift_bits_32("Single bit (MSB)", 0x80000000, 0x80000000);
    test_shift_bits_32("8 bits set scattered", 0x55555555, 0xFF000000);
    test_shift_bits_32("All bits set", 0xFFFFFFFF, 0xFFFFFFFF);
    test_shift_bits_32("Nibble pattern", 0x0F0F0F0F, 0xFF000000);
    test_shift_bits_32("Sequential", 0x12345678, 0xFFFF0000);  /* 13 set bits */

    printf("\n=== Summary ===\n");
    printf("Total tests: %d / %d passed.\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
