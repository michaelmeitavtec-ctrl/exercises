/*
Exercise 11-4: Write a program that counts the number of bits set in an integer.
For example, the number 5 (decimal), which is 0000000000000101 (binary), has
two bits set.
*/
#include <stdio.h>
#include <limits.h>

/**
 * @brief Count the number of bits set in an unsigned integer.
 *
 * Brute force approach: iterate through each bit position and test
 * whether that bit is set using bitwise AND with a mask.
 *
 * Time complexity: O(number of bits in the integer) = O(32) or O(64)
 * Space complexity: O(1)
 *
 * @param value The integer to count bits in.
 * @return The number of set bits (1s in binary representation).
 */
int count_bits_simple(unsigned int value)
{
    int count = 0;

    for (int i = 0; i < (int)sizeof(unsigned int) * 8; ++i) {
        if ((value & (1U << i)) != 0) {
            count++;
        }
    }

    return count;
}

/**
 * @brief Count the number of bits set using Brian Kernighan's algorithm.
 *
 * This algorithm is more efficient because it only iterates as many
 * times as there are set bits, not for every bit position.
 *
 * The key insight: value & (value - 1) clears the rightmost set bit.
 * Why? Subtracting 1 flips all the bits to the right of the rightmost
 * set bit (and the bit itself). AND-ing with the original value clears
 * that rightmost bit and preserves everything else.
 *
 * Example: value = 12 (binary 1100)
 *   value - 1 = 11 (binary 1011)
 *   value & (value - 1) = 1100 & 1011 = 1000 (10 in decimal)
 * Repeat with 10 (binary 1010):
 *   10 - 1 = 9 (binary 1001)
 *   10 & 9 = 1000 (8 in decimal)
 * Repeat with 8 (binary 1000):
 *   8 - 1 = 7 (binary 0111)
 *   8 & 7 = 0000 (0 in decimal)
 * Loop exits. Count = 3. (12 = 1100 in binary has 2 bits set... wait)
 * Actually 12 = 1100 has 2 bits set, so count should be 2 after 2 iterations.
 *
 * Time complexity: O(number of set bits) - much better when bits are sparse
 * Space complexity: O(1)
 *
 * @param value The integer to count bits in.
 * @return The number of set bits.
 */
int count_bits_kernighan(unsigned int value)
{
    int count = 0;

    while (value != 0) {
        value &= (value - 1);  /* Clear the rightmost set bit */
        count++;
    }

    return count;
}

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_count_bits(unsigned int value, int expected)
{
    int result_simple = count_bits_simple(value);
    int result_kernighan = count_bits_kernighan(value);
    tests_run += 2;

    int pass_simple = (result_simple == expected);
    int pass_kernighan = (result_kernighan == expected);

    printf("Value: %10u (0x%08X, binary: ", value, value);
    /* Print binary representation */
    for (int i = 31; i >= 0; --i) {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0 && i > 0) printf("_");
    }
    printf(")\n");

    printf("  Simple:    %2d (Expected: %2d) -> %s\n",
           result_simple, expected, pass_simple ? "PASS" : "FAIL");
    printf("  Kernighan: %2d (Expected: %2d) -> %s\n",
           result_kernighan, expected, pass_kernighan ? "PASS" : "FAIL");
    printf("\n");

    if (pass_simple) tests_passed++;
    if (pass_kernighan) tests_passed++;
}

int main(void)
{
    printf("=== Count Bits Set in Integer ===\n\n");

    /* Test case from the exercise: 5 (binary 0000...0101) has 2 bits set */
    printf("--- Example from Exercise ---\n");
    test_count_bits(5, 2);

    /* Test basic cases */
    printf("--- Basic Cases ---\n");
    test_count_bits(0, 0);       /* No bits set */
    test_count_bits(1, 1);       /* Binary: ...0001 */
    test_count_bits(2, 1);       /* Binary: ...0010 */
    test_count_bits(3, 2);       /* Binary: ...0011 */
    test_count_bits(7, 3);       /* Binary: ...0111 */
    test_count_bits(15, 4);      /* Binary: ...1111 */

    /* Test powers of 2 (only one bit set) */
    printf("--- Powers of 2 (Single Bit Set) ---\n");
    test_count_bits(1, 1);       /* 2^0 */
    test_count_bits(2, 1);       /* 2^1 */
    test_count_bits(4, 1);       /* 2^2 */
    test_count_bits(8, 1);       /* 2^3 */
    test_count_bits(16, 1);      /* 2^4 */
    test_count_bits(256, 1);     /* 2^8 */
    test_count_bits(1024, 1);    /* 2^10 */

    /* Test numbers with all bits set */
    printf("--- All Bits Set (Maximum for bit width) ---\n");
    test_count_bits(0xFF, 8);             /* 8 bits */
    test_count_bits(0xFFFF, 16);          /* 16 bits */
    test_count_bits(0xFFFFFFFF, 32);      /* 32 bits (all for unsigned int) */

    /* Test some interesting patterns */
    printf("--- Interesting Patterns ---\n");
    test_count_bits(0xAAAAAAAA, 16);      /* Alternating 1010... pattern */
    test_count_bits(0x55555555, 16);      /* Alternating 0101... pattern */
    test_count_bits(0x12345678, 13);      /* Random pattern */
    test_count_bits(1000000, 6);          /* 1000000 in binary has 6 bits set */

    /* Test boundary cases */
    printf("--- Boundary Cases ---\n");
    test_count_bits(INT_MAX, 31);         /* All bits except sign bit for signed int */

    printf("\n=== Performance Note ===\n");
    printf("For sparse bit patterns (few bits set), Kernighan's algorithm\n");
    printf("is significantly faster than the simple approach, since it only\n");
    printf("iterates once per set bit rather than once per bit position.\n");

    printf("\nTest Summary: %d / %d tests passed.\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
