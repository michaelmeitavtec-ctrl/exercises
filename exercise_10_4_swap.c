/*
Exercise 10-4: Write a preprocessor macro that swaps two inte gers. (For the real
hacker, write one that does not use a temporary variable declared outside the
macro.)
Specification: A macro that swaps two integers. The basic version uses a temporary variable declared inside the macro itself. The "real hacker" version uses the XOR bitwise trick to swap without any temporary at all — but with important caveats about side effects and multiple evaluation.
*/
#include <stdio.h>
#include <limits.h>

#define TRUE  1
#define FALSE 0

/**
 * @brief Basic swap macro using an internal temporary variable.
 *
 * Uses the do { } while(0) pattern so the macro acts like a single
 * statement and works correctly in all contexts (e.g. inside if/else
 * without braces). The temporary int is scoped to the macro, so
 * there's no risk of name collision with outer scope variables...
 * *except* that if someone declares a variable named 'temp' in the
 * same scope, there will be a conflict. For a production macro,
 * this would suggest using a more exotic name like '__swap_temp__'.
 *
 * Parameters a and b are evaluated once each, so it's safe even if
 * they're expressions with side effects (e.g. array accesses).
 */
#define SWAP(a, b) \
    do { \
        int temp = (a); \
        (a) = (b); \
        (b) = temp; \
    } while (0)

/**
 * @brief "Real hacker" swap using XOR bitwise trick, no temporary var.
 *
 * This uses the property that a ^ b ^ a == b and a ^ b ^ b == a.
 * Sequence:
 *   a ^= b;        // a now holds a^b
 *   b ^= a;        // b now holds (a^b)^b = a
 *   a ^= b;        // a now holds (a^b)^a = b
 *
 * CRITICAL GOTCHAS:
 *   1. SIDE EFFECTS: If a or b is an expression like arr[i++], the
 *      increment happens THREE times (once per line), corrupting i.
 *   2. SAME LOCATION: If a and b refer to the same int (&a == &b),
 *      the result is undefined (you end up XORing a with itself,
 *      zeroing it). But swapping a variable with itself is nonsense
 *      anyway, so this is rarely a real problem.
 *   3. Only works for integers (and other types where ^ is defined).
 *
 * For these reasons, SWAP (the temporary-based version) is actually
 * safer and more readable in real code. This version is here as a
 * pedagogical demonstration of how macros can be clever, and why
 * that cleverness often comes at a cost.
 */
#define SWAP_XOR(a, b) \
    do { \
        (a) ^= (b); \
        (b) ^= (a); \
        (a) ^= (b); \
    } while (0)

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_swap(const char *label, int *x, int *y, int expected_x, int expected_y)
{
    tests_run++;

    int pass = (*x == expected_x && *y == expected_y);
    printf("%-40s -> x=%d, y=%d (Expected: %d, %d) -> %s\n",
           label, *x, *y, expected_x, expected_y, pass ? "PASS" : "FAIL");

    if (pass) {
        tests_passed++;
    }
}

int main(void)
{
    printf("=== SWAP() vs SWAP_XOR() Test Suite ===\n\n");

    /* Test SWAP (temporary-based) */
    printf("--- SWAP (temporary-based) ---\n");

    int a = 5, b = 10;
    SWAP(a, b);
    test_swap("SWAP(5, 10)", &a, &b, 10, 5);

    a = -7; b = 100;
    SWAP(a, b);
    test_swap("SWAP(-7, 100)", &a, &b, 100, -7);

    a = 0; b = 0;
    SWAP(a, b);
    test_swap("SWAP(0, 0)", &a, &b, 0, 0);

    a = INT_MIN; b = INT_MAX;
    SWAP(a, b);
    test_swap("SWAP(INT_MIN, INT_MAX)", &a, &b, INT_MAX, INT_MIN);

    /* Test SWAP_XOR (bitwise trick) */
    printf("\n--- SWAP_XOR (XOR-based) ---\n");

    a = 5; b = 10;
    SWAP_XOR(a, b);
    test_swap("SWAP_XOR(5, 10)", &a, &b, 10, 5);

    a = -7; b = 100;
    SWAP_XOR(a, b);
    test_swap("SWAP_XOR(-7, 100)", &a, &b, 100, -7);

    a = 0; b = 0;
    SWAP_XOR(a, b);
    test_swap("SWAP_XOR(0, 0)", &a, &b, 0, 0);

    a = INT_MIN; b = INT_MAX;
    SWAP_XOR(a, b);
    test_swap("SWAP_XOR(INT_MIN, INT_MAX)", &a, &b, INT_MAX, INT_MIN);

    /* Demonstrate the gotcha: side effects */
    printf("\n--- GOTCHA: Side effects in SWAP_XOR ---\n");
    printf("(This test shows why SWAP_XOR can be dangerous)\n\n");

    int arr[] = {100, 200, 300};
    int i = 0, j = 2;
    printf("Before: arr[i=%d]=%d, arr[j=%d]=%d\n", i, arr[i], j, arr[j]);
    SWAP_XOR(arr[i++], arr[j--]);  /* BUG: i and j are decremented/incremented 3 times each! */
    printf("After SWAP_XOR(arr[i++], arr[j--]): arr[0]=%d, arr[2]=%d, i=%d (Expected: 1), j=%d (Expected: 1)\n",
           arr[0], arr[2], i, j);
    if (i == 1 && j == 1) {
        printf("  i and j incremented/decremented correctly (PASS)\n");
        tests_passed++;
    } else {
        printf("  i=%d, j=%d (expected both 1) -> FAIL (side effects evaluated multiple times!)\n", i, j);
    }
    tests_run++;

    printf("\n--- Compare with SWAP (safe with side effects) ---\n");
    arr[0] = 100; arr[2] = 300;  /* reset */
    i = 0; j = 2;
    printf("Before: arr[i=%d]=%d, arr[j=%d]=%d\n", i, arr[i], j, arr[j]);
    SWAP(arr[i++], arr[j--]);  /* safe: i++ and j-- happen exactly once */
    printf("After SWAP(arr[i++], arr[j--]): arr[0]=%d, arr[2]=%d, i=%d (Expected: 1), j=%d (Expected: 1)\n",
           arr[0], arr[2], i, j);
    if (i == 1 && j == 1) {
        printf("  i and j incremented/decremented correctly (PASS)\n");
        tests_passed++;
    } else {
        printf("  FAIL\n");
    }
    tests_run++;

    printf("\n\nTest Summary: %d / %d tests passed.\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}

    return (tests_passed == tests_run) ? 0 : 1;
}
