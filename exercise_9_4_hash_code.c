/* 
Exercise 9 -4: Write a function that takes a character array and returns a primitive
hash code by adding up the value of each character in the array.
*/

#include <stdio.h>

/**
 * @brief Computes a primitive hash code for a character array by summing
 *        the integer value of every character in it.
 *
 * Definition:
 *   hash = array[0] + array[1] + ... + array[length-1]
 *   (each character's value is its underlying byte/ASCII value)
 *
 * Note: this is a deliberately naive hash. It ignores character order
 * (e.g. "ab" and "ba" produce the same hash) and is prone to collisions,
 * but it satisfies the exercise's definition of "add up the value of
 * each character."
 *
 * @param array  Pointer to the first character of the array.
 * @param length Number of characters in the array.
 * @return Sum of the character values, as an unsigned int (chosen to
 *         reduce the chance of signed overflow on very long arrays;
 *         see note below on wraparound).
 */
unsigned int hash_code(const char array[], int length)
{
    unsigned int hash = 0;

    for (int i = 0; i < length; i++) {
        /* Cast to unsigned char to avoid sign-extension: on platforms
         * where char is signed, characters with values >= 0x80 would
         * otherwise be added as negative numbers. */
        hash += (unsigned char)array[i];
    }

    return hash;
}

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_hash_code(const char *label, const char array[], int length,
                     unsigned int expected)
{
    unsigned int result = hash_code(array, length);
    tests_run++;

    printf("%-30s -> Result: %3u (Expected: %3u) -> %s\n",
           label, result, expected, (result == expected) ? "PASS" : "FAIL");

    if (result == expected) {
        tests_passed++;
    }
}

int main(void)
{
    printf("=== hash_code() Test Suite ===\n\n");

    /* "abc" -> 'a'(97) + 'b'(98) + 'c'(99) = 294 */
    test_hash_code("\"abc\"", "abc", 3, 294);

    /* "a" -> 97 */
    test_hash_code("\"a\"", "a", 1, 97);

    /* empty array -> 0 */
    test_hash_code("\"\" (empty)", "", 0, 0);

    /* "ba" -> same sum as "ab" (collision by design) */
    test_hash_code("\"ab\"", "ab", 2, 195);
    test_hash_code("\"ba\" (collision w/ \"ab\")", "ba", 2, 195);

    /* repeated characters */
    test_hash_code("\"aaaa\"", "aaaa", 4, 388);

    /* mixed case matters: 'A' (65) != 'a' (97) */
    test_hash_code("\"A\"", "A", 1, 65);

    /* digits and symbols */
    test_hash_code("\"123\"", "123", 3, 150); /* '1'+'2'+'3' = 49+50+51 */

    printf("\nTest Summary: %d / %d tests passed.\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
