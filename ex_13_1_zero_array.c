/*
Exercise 13-1: Write a program that uses pointers to set each element of an array
to zero.
*/

#include <stdio.h>
#include <string.h>

/* ---------------------- Array Zeroing Functions ---------------------- */

/**
 * @brief Zero an integer array using pointer arithmetic.
 *
 * This function demonstrates:
 *   - Pointer initialization (point to first element)
 *   - Pointer dereferencing (*ptr = 0)
 *   - Pointer incrementation (ptr++)
 *   - Loop using pointer comparison
 *
 * @param array Pointer to the first element of the array.
 * @param size  Number of elements in the array.
 */
void zero_array_with_pointer(int *array, int size)
{
    int *ptr = array;           /* Point to the beginning of the array */
    int *end = array + size;    /* Point one past the last element */

    /* Increment pointer until we've visited every element */
    while (ptr < end) {
        *ptr = 0;               /* Dereference pointer and set to zero */
        ptr++;                  /* Move to next element */
    }
}

/**
 * @brief Zero an array using pointer arithmetic in a for loop.
 *
 * This is a more compact version using a for loop instead of while.
 *
 * @param array Pointer to the first element of the array.
 * @param size  Number of elements in the array.
 */
void zero_array_for_loop(int *array, int size)
{
    for (int *ptr = array; ptr < array + size; ++ptr) {
        *ptr = 0;
    }
}

/**
 * @brief Zero an array using pointer dereferencing with index notation.
 *
 * Demonstrates that ptr[i] is equivalent to *(ptr + i).
 *
 * @param array Pointer to the first element of the array.
 * @param size  Number of elements in the array.
 */
void zero_array_index_notation(int *array, int size)
{
    for (int i = 0; i < size; ++i) {
        array[i] = 0;  /* Equivalent to *(array + i) = 0 */
    }
}

/**
 * @brief Zero a char array using pointers.
 *
 * Demonstrates that pointer arithmetic works with different types.
 * The pointer increments by sizeof(char) bytes each time.
 *
 * @param array Pointer to the first element of the char array.
 * @param size  Number of elements in the array.
 */
void zero_char_array(char *array, int size)
{
    char *ptr = array;
    char *end = array + size;

    while (ptr < end) {
        *ptr = '\0';  /* Set to null character */
        ++ptr;
    }
}

/**
 * @brief Zero a double array using pointers.
 *
 * Demonstrates pointer arithmetic with larger data types.
 * Each increment moves by sizeof(double) bytes.
 *
 * @param array Pointer to the first element of the double array.
 * @param size  Number of elements in the array.
 */
void zero_double_array(double *array, int size)
{
    for (double *ptr = array; ptr < array + size; ++ptr) {
        *ptr = 0.0;
    }
}

/**
 * @brief Zero an array using pointer-to-pointer (advanced).
 *
 * Demonstrates modifying a pointer through a pointer to that pointer.
 *
 * @param array_ptr Pointer to the array pointer.
 * @param size      Number of elements in the array.
 */
void zero_array_pointer_to_pointer(int **array_ptr, int size)
{
    int *ptr = *array_ptr;      /* Dereference to get the actual array pointer */
    int *end = *array_ptr + size;

    while (ptr < end) {
        *ptr = 0;
        ++ptr;
    }
}

/**
 * @brief Zero an array by passing a pointer range (start and end).
 *
 * Useful when you want to zero only a portion of an array.
 *
 * @param start Pointer to the first element to zero.
 * @param end   Pointer one past the last element to zero.
 */
void zero_array_range(int *start, int *end)
{
    while (start < end) {
        *start = 0;
        ++start;
    }
}

/* ---------------------- Display Functions ---------------------- */

/**
 * @brief Print an integer array.
 *
 * @param array Pointer to the first element.
 * @param size  Number of elements.
 */
void print_int_array(const int *array, int size)
{
    printf("[");
    for (int i = 0; i < size; ++i) {
        printf("%d", array[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

/**
 * @brief Print a double array.
 *
 * @param array Pointer to the first element.
 * @param size  Number of elements.
 */
void print_double_array(const double *array, int size)
{
    printf("[");
    for (int i = 0; i < size; ++i) {
        printf("%.1f", array[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

/**
 * @brief Verify that all elements in an array are zero.
 *
 * @param array Pointer to the first element.
 * @param size  Number of elements.
 * @return 1 if all elements are zero, 0 otherwise.
 */
int all_zeros(const int *array, int size)
{
    for (int i = 0; i < size; ++i) {
        if (array[i] != 0) {
            return 0;
        }
    }
    return 1;
}

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_zero_array(const char *label, void (*zero_func)(int *, int),
                     int array[], int size)
{
    printf("%-40s\n", label);
    printf("  Before: ");
    print_int_array(array, size);

    zero_func(array, size);

    printf("  After:  ");
    print_int_array(array, size);

    int pass = all_zeros(array, size);
    printf("  Result: %s\n\n", pass ? "PASS" : "FAIL");

    tests_run++;
    if (pass) tests_passed++;
}

int main(void)
{
    printf("=== Using Pointers to Zero an Array ===\n\n");

    /* Test 1: Small array with pointer incrementation (while loop) */
    printf("--- Test 1: Small Array (while loop with pointer++) ---\n");
    int arr1[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);

    test_zero_array("Small array (5 elements)", zero_array_with_pointer, arr1, size1);

    /* Test 2: Same array, different function (for loop) */
    printf("--- Test 2: Same Array Type (for loop with pointer) ---\n");
    int arr2[] = {10, 20, 30, 40, 50};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    test_zero_array("For loop variant", zero_array_for_loop, arr2, size2);

    /* Test 3: Index notation (equivalent but different style) */
    printf("--- Test 3: Index Notation (arr[i] style) ---\n");
    int arr3[] = {7, 8, 9, 10, 11};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    test_zero_array("Index notation (ptr[i])", zero_array_index_notation, arr3, size3);

    /* Test 4: Large array */
    printf("--- Test 4: Large Array ---\n");
    int arr4[100];
    for (int i = 0; i < 100; ++i) {
        arr4[i] = i;
    }
    int size4 = sizeof(arr4) / sizeof(arr4[0]);

    printf("Large array (100 elements)\n");
    printf("  Before: [0, 1, 2, 3, ..., 99]\n");

    zero_array_with_pointer(arr4, size4);

    int pass = all_zeros(arr4, size4);
    printf("  After:  [0, 0, 0, 0, ..., 0]\n");
    printf("  Result: %s\n\n", pass ? "PASS" : "FAIL");

    tests_run++;
    if (pass) tests_passed++;

    /* Test 5: Single element array */
    printf("--- Test 5: Single Element Array ---\n");
    int arr5[] = {42};
    int size5 = 1;

    test_zero_array("Single element", zero_array_with_pointer, arr5, size5);

    /* Test 6: Empty array (edge case) */
    printf("--- Test 6: Empty Array (size 0) ---\n");
    int arr6[] = {99};  /* Array exists but we'll pass size 0 */
    int size6 = 0;

    printf("Empty array (size 0)\n");
    printf("  Before: [99]\n");

    zero_array_with_pointer(arr6, size6);

    printf("  After:  (no elements to zero)\n");
    printf("  Original array untouched: [%d]\n", arr6[0]);
    printf("  Result: PASS (correctly did nothing)\n\n");

    tests_run++;
    tests_passed++;  /* This test always passes */

    /* Test 7: Char array */
    printf("--- Test 7: Char Array ---\n");
    char char_arr[] = {'a', 'b', 'c', 'd', 'e'};
    int char_size = sizeof(char_arr) / sizeof(char_arr[0]);

    printf("Char array\n");
    printf("  Before: ['a', 'b', 'c', 'd', 'e']\n");

    zero_char_array(char_arr, char_size);

    int char_pass = 1;
    for (int i = 0; i < char_size; ++i) {
        if (char_arr[i] != '\0') {
            char_pass = 0;
            break;
        }
    }

    printf("  After:  [all null characters]\n");
    printf("  Result: %s\n\n", char_pass ? "PASS" : "FAIL");

    tests_run++;
    if (char_pass) tests_passed++;

    /* Test 8: Double array */
    printf("--- Test 8: Double Array ---\n");
    double dbl_arr[] = {3.14, 2.71, 1.41, 1.73, 2.23};
    int dbl_size = sizeof(dbl_arr) / sizeof(dbl_arr[0]);

    printf("Double array\n");
    printf("  Before: ");
    print_double_array(dbl_arr, dbl_size);

    zero_double_array(dbl_arr, dbl_size);

    int dbl_pass = 1;
    for (int i = 0; i < dbl_size; ++i) {
        if (dbl_arr[i] != 0.0) {
            dbl_pass = 0;
            break;
        }
    }

    printf("  After:  ");
    print_double_array(dbl_arr, dbl_size);
    printf("  Result: %s\n\n", dbl_pass ? "PASS" : "FAIL");

    tests_run++;
    if (dbl_pass) tests_passed++;

    /* Test 9: Pointer-to-pointer version */
    printf("--- Test 9: Pointer-to-Pointer Version ---\n");
    int arr9[] = {11, 22, 33, 44, 55};
    int *ptr_to_arr = arr9;  /* Create a pointer to the array */
    int size9 = sizeof(arr9) / sizeof(arr9[0]);

    printf("Pointer-to-pointer\n");
    printf("  Before: ");
    print_int_array(arr9, size9);

    zero_array_pointer_to_pointer(&ptr_to_arr, size9);

    printf("  After:  ");
    print_int_array(arr9, size9);

    int ptr2_pass = all_zeros(arr9, size9);
    printf("  Result: %s\n\n", ptr2_pass ? "PASS" : "FAIL");

    tests_run++;
    if (ptr2_pass) tests_passed++;

    /* Test 10: Partial array zeroing (range) */
    printf("--- Test 10: Partial Array (Range Zeroing) ---\n");
    int arr10[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size10 = sizeof(arr10) / sizeof(arr10[0]);

    printf("Partial zeroing (elements 2-6)\n");
    printf("  Before: ");
    print_int_array(arr10, size10);

    /* Zero elements from index 2 to 6 (not including 6) */
    zero_array_range(&arr10[2], &arr10[6]);

    printf("  After:  ");
    print_int_array(arr10, size10);

    int range_pass = (arr10[0] == 1 && arr10[1] == 2 &&
                      arr10[2] == 0 && arr10[3] == 0 &&
                      arr10[4] == 0 && arr10[5] == 0 &&
                      arr10[6] == 7 && arr10[9] == 10);

    printf("  Result: %s (first two and last three untouched)\n\n",
           range_pass ? "PASS" : "FAIL");

    tests_run++;
    if (range_pass) tests_passed++;

    /* Summary */
    printf("=== Test Summary ===\n");
    printf("Passed: %d / %d tests\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
