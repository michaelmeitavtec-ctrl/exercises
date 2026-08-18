/*
Exercise 11-5: Write a program that takes a 32 -bit integer (long int) and splits it
into eight 4-bit values. (Be careful of the sign bit.)
*/
#include <stdio.h>
#include <limits.h>

/**
 * @brief Extract a single 4-bit nibble from a 32-bit unsigned integer.
 *
 * @param value The 32-bit unsigned integer.
 * @param nibble_index Index of the nibble (0-7), where 0 is the rightmost
 *                     (least significant) nibble.
 * @return The extracted 4-bit value (0-15).
 */
#define GET_NIBBLE(value, nibble_index) \
    (((value) >> ((nibble_index) * 4)) & 0xF)

/**
 * @brief Split a 32-bit integer into eight 4-bit nibbles.
 *
 * @param value The 32-bit signed integer to split.
 * @param nibbles Pointer to an array of at least 8 unsigned char values.
 *                On return, nibbles[0] is the least significant nibble,
 *                and nibbles[7] is the most significant nibble.
 *
 * Note: We cast to unsigned int to avoid sign-extension issues. This
 * reinterprets the bit pattern of the signed value as unsigned, which
 * is safe and avoids UB.
 */
void split_into_nibbles(long int value, unsigned char nibbles[8])
{
    unsigned int unsigned_value = (unsigned int)value;

    for (int i = 0; i < 8; ++i) {
        nibbles[i] = GET_NIBBLE(unsigned_value, i);
    }
}

/* ---------------------- Helper Functions ---------------------- */

/**
 * @brief Print a 32-bit unsigned integer in binary.
 */
void print_binary(unsigned int value)
{
    for (int i = 31; i >= 0; --i) {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0 && i > 0) printf("_");
    }
}

/**
 * @brief Print the nibbles in various formats.
 */
void print_nibbles(unsigned char nibbles[8])
{
    printf("  Hex:     ");
    for (int i = 7; i >= 0; --i) {
        printf("%X", nibbles[i]);
    }
    printf("\n");

    printf("  Decimal: ");
    for (int i = 7; i >= 0; --i) {
        printf("%2d ", nibbles[i]);
    }
    printf("\n");

    printf("  Binary:  ");
    for (int i = 7; i >= 0; --i) {
        for (int bit = 3; bit >= 0; --bit) {
            printf("%d", (nibbles[i] >> bit) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_split_nibbles(const char *label, long int value,
                        unsigned char expected[8])
{
    unsigned char result[8];
    split_into_nibbles(value, result);
    tests_run++;

    int pass = 1;
    for (int i = 0; i < 8; ++i) {
        if (result[i] != expected[i]) {
            pass = 0;
            break;
        }
    }

    printf("%-40s\n", label);
    printf("  Value:   0x%08lX (", (unsigned long)value);
    print_binary((unsigned int)value);
    printf(")\n");

    printf("  Result:  [");
    for (int i = 7; i >= 0; --i) {
        printf("%d", result[i]);
        if (i > 0) printf(",");
    }
    printf("]\n");

    printf("  Expected: [");
    for (int i = 7; i >= 0; --i) {
        printf("%d", expected[i]);
        if (i > 0) printf(",");
    }
    printf("]\n");

    printf("  Result:  %s\n\n", pass ? "PASS" : "FAIL");

    if (pass) {
        tests_passed++;
    }
}

int main(void)
{
    printf("=== Split 32-bit Integer into Eight 4-bit Nibbles ===\n\n");

    /* Test 1: Zero */
    printf("--- Zero ---\n");
    unsigned char expected_zero[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    test_split_nibbles("Value: 0", 0, expected_zero);

    /* Test 2: All bits set (0xFFFFFFFF, or -1 in signed representation) */
    printf("--- All Bits Set (0xFFFFFFFF / -1) ---\n");
    unsigned char expected_all_ones[8] = {0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF};
    test_split_nibbles("Value: -1 (all bits set)", -1, expected_all_ones);

    /* Test 3: Single bit set in each position */
    printf("--- Single Nibbles ---\n");
    unsigned char expected_single[8] = {0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    test_split_nibbles("Value: 0x00000001 (nibble 0 = 1)", 0x00000001, expected_single);

    unsigned char expected_single_2[8] = {0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    test_split_nibbles("Value: 0x00000010 (nibble 1 = 1)", 0x00000010, expected_single_2);

    unsigned char expected_single_7[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1};
    test_split_nibbles("Value: 0x10000000 (nibble 7 = 1)", 0x10000000, expected_single_7);

    /* Test 4: Alternating pattern */
    printf("--- Alternating Pattern ---\n");
    unsigned char expected_alt[8] = {0xA, 0x5, 0xA, 0x5, 0xA, 0x5, 0xA, 0x5};
    test_split_nibbles("Value: 0xA5A5A5A5 (alternating)", 0xA5A5A5A5, expected_alt);

    /* Test 5: Sequential values */
    printf("--- Sequential Values ---\n");
    unsigned char expected_seq[8] = {0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 0x0};
    test_split_nibbles("Value: 0x01234567 (sequential)", 0x01234567, expected_seq);

    /* Test 6: Negative number (sign bit set) */
    printf("--- Negative Number (Sign Bit Set) ---\n");
    unsigned char expected_neg[8] = {0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF};
    test_split_nibbles("Value: -1 (0xFFFFFFFF, sign bit = 1)", -1, expected_neg);

    unsigned char expected_neg_2[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8};
    test_split_nibbles("Value: -2147483648 (0x80000000, sign bit = 1)", 
                       (long int)0x80000000, expected_neg_2);

    /* Test 7: Maximum positive 32-bit signed integer */
    printf("--- Maximum Positive Signed 32-bit ---\n");
    unsigned char expected_max[8] = {0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0x7};
    test_split_nibbles("Value: INT_MAX (0x7FFFFFFF)", INT_MAX, expected_max);

    /* Test 8: Demonstrating that nibbles can be used to reconstruct the value */
    printf("--- Reconstruction Test ---\n");
    long int original = 0x3C5A1B42;
    unsigned char nibbles[8];
    split_into_nibbles(original, nibbles);

    unsigned int reconstructed = 0;
    for (int i = 0; i < 8; ++i) {
        reconstructed |= ((unsigned int)nibbles[i] << (i * 4));
    }

    printf("Original:      0x%08lX (", (unsigned long)original);
    print_binary((unsigned int)original);
    printf(")\n");

    printf("Reconstructed: 0x%08X (", reconstructed);
    print_binary(reconstructed);
    printf(")\n");

    if (reconstructed == (unsigned int)original) {
        printf("Result: PASS (reconstruction successful)\n\n");
        tests_passed++;
    } else {
        printf("Result: FAIL (reconstruction mismatch)\n\n");
    }
    tests_run++;

    printf("\n=== Test Summary ===\n");
    printf("%d / %d tests passed.\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
