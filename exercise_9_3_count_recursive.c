#include <stdio.h>

/**
 * Write a function count(number, array, length) that counts the
number of times number appears in array. 

*The array has length elements. The function should be recursive. 
 
 *Write a test program to go with the function.
 * @brief Recursively counts occurrences of `number` in the first
 *        `length` elements of `array`.
 *
 * Recursion strategy:
 *   Base case: length == 0 -> no elements to check -> count is 0.
 *   Recursive case: check whether the last element (index length-1)
 *                   equals number, then add that to the count of
 *                   occurrences in the remaining (length-1) elements.
 *
 * @param number The value to search for.
 * @param array  Pointer to the first element of the array.
 * @param length Number of elements in array to examine.
 * @return The number of times number appears in array[0..length-1].
 */
int count(int number, int array[], int length)
{
    if (length <= 0) {
        return 0;                 /* base case: nothing left to check */
    }

    int match = (array[length - 1] == number) ? 1 : 0;
    return match + count(number, array, length - 1);
}

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_count(int number, int array[], int length, int expected)
{
    int result = count(number, array, length);
    tests_run++;

    printf("Searching for %d in array of length %d -> ", number, length);
    printf("Result: %d (Expected: %d) -> %s\n",
           result, expected, (result == expected) ? "PASS" : "FAIL");

    if (result == expected) {
        tests_passed++;
    }
}

int main(void)
{
    printf("=== Recursive count() Test Suite ===\n\n");

    int a[] = {1, 2, 3, 2, 4, 2, 5};
    int len_a = sizeof(a) / sizeof(a[0]);

    int b[] = {7, 7, 7, 7, 7};
    int len_b = sizeof(b) / sizeof(b[0]);

    int c[] = {0};  /* placeholder element; we pass length 0 so it's never read */

    int d[] = {-1, 0, -1, 5, -1, -1};
    int len_d = sizeof(d) / sizeof(d[0]);

    test_count(2, a, len_a, 3);   /* 2 appears 3 times */
    test_count(1, a, len_a, 1);   /* 1 appears once */
    test_count(9, a, len_a, 0);   /* 9 doesn't appear */
    test_count(7, b, len_b, 5);   /* every element matches */
    test_count(3, b, len_b, 0);   /* nothing matches */
    test_count(0, c, 0, 0);       /* empty array -> 0 */
    test_count(-1, d, len_d, 4);  /* -1 appears at indices 0, 2, 4, 5 -> 4 times */
    test_count(5, d, len_d, 1);   /* 5 appears once */

    printf("\nTest Summary: %d / %d tests passed.\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
