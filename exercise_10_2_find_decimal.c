/*
Exercise 10-2: Write a macro is_digit that returns TRUE if its argument is a
decimal digit.
*/
#include <stdio.h>

#define TRUE  1
#define FALSE 0

/**
 * @brief Evaluates to TRUE if c is a decimal digit character ('0'-'9'),
 *        FALSE otherwise.
 *
 * Relies on the C standard guarantee that the digit characters '0'
 * through '9' are contiguous and in ascending order in every character
 * set C supports (this is guaranteed by the C standard, unlike letters,
 * which are NOT guaranteed contiguous in all encodings).
 *
 * Parameter c is parenthesized everywhere it's used, and the whole
 * macro body is parenthesized, so it composes safely inside larger
 * expressions and is safe even when called with a compound expression.
 */
#define is_digit(c) (((c) >= '0' && (c) <= '9') ? TRUE : FALSE)

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_is_digit(char c, int expected)
{
    int result = is_digit(c);
    tests_run++;

    printf("'%c' -> Result: %-5s (Expected: %-5s) -> %s\n",
           c,
           result ? "TRUE" : "FALSE",
           expected ? "TRUE" : "FALSE",
           (result == expected) ? "PASS" : "FAIL");

    if (result == expected) {
        tests_passed++;
    }
}

int main(void)
{
    printf("=== is_digit() Test Suite ===\n\n");

    /* All decimal digits should be TRUE */
    test_is_digit('0', TRUE);
    test_is_digit('1', TRUE);
    test_is_digit('5', TRUE);
    test_is_digit('9', TRUE);

    /* Letters should be FALSE */
    test_is_digit('a', FALSE);
    test_is_digit('Z', FALSE);

    /* Characters adjacent to the digit range in ASCII should be FALSE
     * (boundary tests: '/' is 0x2F, just before '0'; ':' is 0x3A,
     * just after '9') */
    test_is_digit('/', FALSE);
    test_is_digit(':', FALSE);

    /* Whitespace and punctuation should be FALSE */
    test_is_digit(' ', FALSE);
    test_is_digit('-', FALSE);
    test_is_digit('.', FALSE);

    printf("\nTest Summary: %d / %d tests passed.\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
