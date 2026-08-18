/*
Exercise 10-3: Write a second macro is_hex that returns true if its argument is a
hex digit (0-9, A-F, a-f). The second macro should reference the first.
*/
#include <stdio.h>

#define TRUE  1
#define FALSE 0

/**
 * @brief Evaluates to TRUE if c is a decimal digit character ('0'-'9'),
 *        FALSE otherwise.
 *
 * Relies on the C standard guarantee that '0'-'9' are contiguous and
 * in ascending order in the execution character set.
 */
#define is_digit(c) (((c) >= '0' && (c) <= '9') ? TRUE : FALSE)

/**
 * @brief Evaluates to TRUE if c is a valid hexadecimal digit character:
 *        '0'-'9', 'A'-'F', or 'a'-'f'. FALSE otherwise.
 *
 * Reuses is_digit(c) for the numeric portion of the check, then adds
 * the upper-case and lower-case hex letter ranges. Unlike '0'-'9',
 * the letter ranges 'A'-'F' and 'a'-'f' are contiguous and ordered in
 * ASCII, but that contiguity is NOT guaranteed by the C standard for
 * all character sets — this macro is therefore portable for its digit
 * portion but relies on ASCII-like ordering for its letter portion,
 * which is true of every character set in practical use today.
 *
 * c is parenthesized everywhere it appears, and is_digit(c) expands
 * c exactly once per use inside is_digit, so no double-evaluation
 * surprises beyond what is_digit itself already has.
 */
#define is_hex(c) \
    ((is_digit(c) || \
      ((c) >= 'A' && (c) <= 'F') || \
      ((c) >= 'a' && (c) <= 'f')) ? TRUE : FALSE)

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_is_hex(char c, int expected)
{
    int result = is_hex(c);
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
    printf("=== is_hex() Test Suite ===\n\n");

    /* Decimal digits should be TRUE (via is_digit) */
    test_is_hex('0', TRUE);
    test_is_hex('5', TRUE);
    test_is_hex('9', TRUE);

    /* Uppercase hex letters A-F should be TRUE */
    test_is_hex('A', TRUE);
    test_is_hex('C', TRUE);
    test_is_hex('F', TRUE);

    /* Lowercase hex letters a-f should be TRUE */
    test_is_hex('a', TRUE);
    test_is_hex('c', TRUE);
    test_is_hex('f', TRUE);

    /* Non-hex letters should be FALSE */
    test_is_hex('G', FALSE);
    test_is_hex('g', FALSE);
    test_is_hex('Z', FALSE);
    test_is_hex('z', FALSE);

    /* Boundary characters just outside each valid range */
    test_is_hex('/', FALSE);  /* just before '0' */
    test_is_hex(':', FALSE);  /* just after '9' */
    test_is_hex('@', FALSE);  /* just before 'A' */
    test_is_hex('G', FALSE);  /* just after 'F' (duplicate check, kept for clarity) */
    test_is_hex('`', FALSE);  /* just before 'a' */
    test_is_hex('g', FALSE);  /* just after 'f' (duplicate check, kept for clarity) */

    /* Non-alphanumeric */
    test_is_hex(' ', FALSE);
    test_is_hex('-', FALSE);
    test_is_hex('#', FALSE);

    printf("\nTest Summary: %d / %d tests passed.\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
