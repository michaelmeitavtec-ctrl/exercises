/*
Exercise 10-1: Write a macro that returns TRUE if its parameter is divisible by 10
and FALSE otherwise.
*/
#include <stdio.h>

#define TRUE  1
#define FALSE 0

/**
 * @brief Evaluates to TRUE if x is evenly divisible by 10, FALSE otherwise.
 *
 * Both the macro body and the parameter x are individually parenthesized,
 * so it's safe to call with expressions (e.g. DIVISIBLE_BY_TEN(a + b))
 * and safe to compose inside larger expressions (e.g. !DIVISIBLE_BY_TEN(x)).
 *
 * Works correctly for negative numbers too, since -10 % 10 == 0 in C.
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

    /* Direct macro invocation with an expression argument, to actually
     * prove the parentheses around x matter (see notes below). */
    printf("\nDirect macro test: DIVISIBLE_BY_TEN(5 + 5) -> %s\n",
           DIVISIBLE_BY_TEN(5 + 5) ? "TRUE" : "FALSE");

    printf("\nTest Summary: %d / %d tests passed.\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
