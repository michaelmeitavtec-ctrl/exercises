#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

/**
 * @brief Finds the maximum value in an array of integers.
 *
 * @param array  Pointer to the first element of the array.
 * @param length Number of elements in the array.
 * @param found  Output parameter: set to true if a maximum was found
 *               (i.e., length > 0), false if the array was empty.
 * @return The maximum value in array[0..length-1]. If length == 0,
 *         the return value is unspecified (0) and *found is set to
 *         false — callers must check *found before using the result.
 */
int max_value(const int array[], int length, bool *found)
{
    if (length <= 0) {
        *found = false;
        return 0;  /* unspecified/placeholder; caller must check *found */
    }

    int max = array[0];
    for (int i = 1; i < length; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    *found = true;
    return max;
}

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_max_value(const char *label, const int array[], int length,
                     bool expected_found, int expected_value)
{
    bool found;
    int result = max_value(array, length, &found);
    tests_run++;

    bool pass;
    if (!expected_found) {
        pass = (found == false);
        printf("%-30s -> found: %-5s (Expected: false) -> %s\n",
               label, found ? "true" : "false", pass ? "PASS" : "FAIL");
    } else {
        pass = (found == true && result == expected_value);
        printf("%-30s -> max: %4d (Expected: %4d) -> %s\n",
               label, result, expected_value, pass ? "PASS" : "FAIL");
    }

    if (pass) {
        tests_passed++;
    }
}

int main(void)
{
    printf("=== max_value() Test Suite ===\n\n");

    int a[] = {3, 7, 2, 9, 4};
    int len_a = sizeof(a) / sizeof(a[0]);

    int b[] = {-5, -1, -20, -3};
    int len_b = sizeof(b) / sizeof(b[0]);

    int c[] = {42};

    int d[] = {5, 5, 5, 5};
    int len_d = sizeof(d) / sizeof(d[0]);

    int e[] = {0};  /* placeholder; used with length 0 to test empty case */

    int f[] = {INT_MIN, 0, INT_MAX, -100};
    int len_f = sizeof(f) / sizeof(f[0]);

    test_max_value("{3,7,2,9,4}",          a, len_a, true, 9);
    test_max_value("{-5,-1,-20,-3}",       b, len_b, true, -1);
    test_max_value("{42}",                 c, 1,     true, 42);
    test_max_value("{5,5,5,5} (all tied)", d, len_d, true, 5);
    test_max_value("empty array",          e, 0,     false, 0);
    test_max_value("{INT_MIN,0,INT_MAX,-100}", f, len_f, true, INT_MAX);

    printf("\nTest Summary: %d / %d tests passed.\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
    return (tests_passed == tests_run) ? 0 : 1;
}
