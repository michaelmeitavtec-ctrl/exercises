#include <stdio.h>

#define TRUE  1
#define FALSE 0

/**
 * @brief Evaluates to TRUE if x is evenly divisible by 10, FALSE otherwise.
 *
 * Parenthesization notes (see prior exercises for why these matter):
 *   - The whole macro body is wrapped in parentheses so it composes
 *     safely inside larger expressions (e.g. !DIVISIBLE_BY_TEN(x)).
 *   - The parameter x is individually wrapped in parentheses every
 *     place it's used, so it's safe even if called with an expression
 *     like DIVISIBLE_BY_TEN(a + b) rather than a single variable.
 *
 * Works for negative numbers too: in C, -10 % 10 == 0, and more
 * generally x % 10 == 0 whenever x is a multiple of 10, positive,
 * negative, or zero.
 */
#define DIVISIBLE_BY_TEN(x) (((x) % 10) == 0 ? TRUE : FALSE)

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_divisible_by_ten(int value, int expected)
{
    int result = DIVISIBLE_BY_TEN(value);
    tests_run++;

    printf("%-6d -> Result: %-5s (Expected: %-5s) -> %s\n",
           value,
           result ? "TRUE" : "FALSE",
           expected ? "TRUE" : "FALSE",
           (result == expected) ? "PASS" : "FAIL");

    if (result == expected) {
        tests_passed++;
    }
}

int main(void)
{
    printf("=== DIVISIBLE_BY_TEN() Test Suite ===\n\n");

    test_divisible_by_ten(10,   TRUE);
    test_divisible_by_ten(0,    TRUE);
    test_divisible_by_ten(100,  TRUE);
    test_divisible_by_ten(-10,  TRUE);
    test_divisible_by_ten(-20,  TRUE);
    test_divisible_by_ten(7,    FALSE);
    test_divisible_by_ten(15,   FALSE);
    test_divisible_by_ten(99,   FALSE);
    test_divisible_by_ten(-7,   FALSE);
    test_divisible_by_ten(1,    FALSE);

    /* Demonstrates why the parentheses around x matter: without them,
     * DIVISIBLE_BY_TEN(5 + 5) could expand incorrectly. */
    test_divisible_by_ten(5 + 5, TRUE);  /* 5 + 5 = 10, divisible by 10 */

    printf("\nTest Summary: %d / %d tests passed.\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
