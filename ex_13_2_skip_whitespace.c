/*
Exercise 13-2: Write a function that takes a single string as its argument and
returns a pointer to the first nonwhite character in the string.
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**
 * @brief Find the first nonwhitespace character in a string.
 *
 * Whitespace is defined as any character for which isspace() returns true:
 * space, tab ('\t'), newline ('\n'), carriage return ('\r'),
 * vertical tab ('\v'), and form feed ('\f').
 *
 * Algorithm:
 *   1. Check for NULL pointer
 *   2. Iterate through the string using pointer arithmetic
 *   3. Skip characters where isspace() is true
 *   4. Return pointer to first non-whitespace character
 *   5. If end of string reached, return pointer to the null terminator
 *
 * @param str Pointer to the input string (may be NULL).
 * @return Pointer to the first nonwhitespace character, or pointer to
 *         null terminator if no nonwhitespace found. Returns NULL if
 *         input is NULL.
 *
 * Example:
 *   Input:  "   hello world"
 *   Output: pointer to 'h'
 *
 *   Input:  "   \t\n"
 *   Output: pointer to '\0' (end of string)
 */
char *skip_whitespace(const char *str)
{
    /* Guard against NULL pointer */
    if (str == NULL) {
        return NULL;
    }

    /* Use pointer arithmetic to traverse the string */
    const char *ptr = str;

    /* Continue while current character is whitespace */
    while (*ptr != '\0' && isspace((unsigned char)*ptr)) {
        ptr++;
    }

    /* Return pointer to first non-whitespace character (or null terminator) */
    return (char *)ptr;  /* Cast away const for the return */
}

/**
 * @brief Alternative version using manual whitespace check (no ctype.h).
 *
 * This version doesn't rely on isspace(), which is useful if you want
 * to define whitespace differently or avoid the library function.
 *
 * @param str Pointer to the input string.
 * @return Pointer to the first nonwhitespace character.
 */
char *skip_whitespace_manual(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    const char *ptr = str;

    /* Skip only space, tab, newline, carriage return */
    while (*ptr != '\0' && 
           (*ptr == ' ' || *ptr == '\t' || 
            *ptr == '\n' || *ptr == '\r')) {
        ptr++;
    }

    return (char *)ptr;
}

/**
 * @brief More concise version using pointer post-increment.
 *
 * Demonstrates compact pointer manipulation.
 *
 * @param str Pointer to the input string.
 * @return Pointer to the first nonwhitespace character.
 */
char *skip_whitespace_compact(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    /* Use pointer post-increment in the while condition */
    while (*str && isspace((unsigned char)*str)) {
        str++;
    }

    return (char *)str;
}

/* ---------------------- Helper Functions ---------------------- */

/**
 * @brief Check if a pointer points to the null terminator.
 *
 * @param ptr Pointer to check.
 * @return 1 if ptr points to '\0', 0 otherwise.
 */
int is_null_terminator(const char *ptr)
{
    return ptr != NULL && *ptr == '\0';
}

/**
 * @brief Print a string with visible whitespace markers.
 *
 * Useful for debugging strings containing whitespace.
 *
 * @param str Pointer to the string.
 */
void print_string_visible_whitespace(const char *str)
{
    if (str == NULL) {
        printf("(NULL)");
        return;
    }

    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == ' ') {
            printf("·");  /* Dot for space */
        } else if (str[i] == '\t') {
            printf("→");  /* Arrow for tab */
        } else if (str[i] == '\n') {
            printf("↓");  /* Down arrow for newline */
        } else {
            printf("%c", str[i]);
        }
    }
}

/**
 * @brief Get a human-readable description of what a pointer points to.
 *
 * @param ptr Pointer to describe.
 * @return String describing the pointer's target.
 */
const char *describe_pointer(const char *ptr)
{
    if (ptr == NULL) {
        return "(NULL pointer)";
    }
    if (*ptr == '\0') {
        return "(null terminator)";
    }
    return "(valid character)";
}

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_skip_whitespace(const char *label, const char *input,
                           const char *expected_char)
{
    printf("%-50s\n", label);
    printf("  Input:  \"");
    print_string_visible_whitespace(input);
    printf("\"\n");

    char *result = skip_whitespace(input);

    printf("  Result: ");
    if (result == NULL) {
        printf("(NULL pointer) -> FAIL (should not return NULL)\n");
        printf("\n");
        tests_run++;
        return;
    }

    printf("%s -> ", describe_pointer(result));

    if (expected_char == NULL) {
        /* Expect pointer to null terminator */
        if (*result == '\0') {
            printf("PASS (points to null terminator)\n");
            tests_passed++;
        } else {
            printf("FAIL (expected null terminator, got '%c')\n", *result);
        }
    } else {
        /* Expect pointer to specific character */
        if (*result != '\0' && *result == expected_char[0]) {
            printf("PASS (points to '%c')\n", *result);
            tests_passed++;
        } else if (*result == '\0') {
            printf("FAIL (expected '%c', got null terminator)\n", 
                   expected_char[0]);
        } else {
            printf("FAIL (expected '%c', got '%c')\n", 
                   expected_char[0], *result);
        }
    }

    printf("\n");
    tests_run++;
}

void test_skip_whitespace_with_offset(const char *label, const char *input,
                                       int expected_offset)
{
    printf("%-50s\n", label);
    printf("  Input:  \"");
    print_string_visible_whitespace(input);
    printf("\"\n");

    char *result = skip_whitespace(input);

    if (result == NULL) {
        printf("  Result: (NULL pointer) -> FAIL\n\n");
        tests_run++;
        return;
    }

    int actual_offset = (int)(result - input);

    printf("  Offset: %d bytes (Expected: %d bytes) -> %s\n",
           actual_offset, expected_offset,
           actual_offset == expected_offset ? "PASS" : "FAIL");

    if (actual_offset == expected_offset) {
        tests_passed++;
    }

    printf("\n");
    tests_run++;
}

int main(void)
{
    printf("=== Find First Nonwhitespace Character ===\n\n");

    /* Test 1: String with leading spaces */
    printf("--- Test 1: Leading Spaces ---\n");
    test_skip_whitespace("Leading spaces",
                         "   hello world", "h");

    /* Test 2: String with leading tabs */
    printf("--- Test 2: Leading Tabs ---\n");
    test_skip_whitespace("Leading tabs",
                         "\t\t\tworld", "w");

    /* Test 3: String with mixed whitespace */
    printf("--- Test 3: Mixed Whitespace ---\n");
    test_skip_whitespace("Spaces, tabs, newlines",
                         "  \t  \n  alpha", "a");

    /* Test 4: No leading whitespace */
    printf("--- Test 4: No Leading Whitespace ---\n");
    test_skip_whitespace("No whitespace",
                         "hello world", "h");

    /* Test 5: All whitespace string */
    printf("--- Test 5: All Whitespace ---\n");
    test_skip_whitespace("Only whitespace",
                         "   \t\t  \n  ", NULL);

    /* Test 6: Empty string */
    printf("--- Test 6: Empty String ---\n");
    test_skip_whitespace("Empty string",
                         "", NULL);

    /* Test 7: Single character (no whitespace) */
    printf("--- Test 7: Single Character ---\n");
    test_skip_whitespace("Single nonwhite char",
                         "X", "X");

    /* Test 8: Single space */
    printf("--- Test 8: Single Space ---\n");
    test_skip_whitespace("Single space",
                         " ", NULL);

    /* Test 9: Pointer offset calculation */
    printf("--- Test 9: Pointer Offset Calculation ---\n");
    test_skip_whitespace_with_offset("5 leading spaces",
                                      "     start", 5);

    test_skip_whitespace_with_offset("3 tabs + 2 spaces",
                                      "\t\t\t  end", 5);

    /* Test 10: Whitespace at end of word */
    printf("--- Test 10: Whitespace After Text ---\n");
    test_skip_whitespace("Text followed by spaces",
                         "word   ", "w");

    /* Test 11: Various whitespace characters */
    printf("--- Test 11: Various Whitespace Types ---\n");
    {
        const char space_test[] = "   x";
        const char tab_test[] = "\t\tx";
        const char newline_test[] = "\n\nx";
        const char cr_test[] = "\r\rx";
        const char mixed_test[] = " \t\n\rx";

        test_skip_whitespace("Spaces", space_test, "x");
        test_skip_whitespace("Tabs", tab_test, "x");
        test_skip_whitespace("Newlines", newline_test, "x");
        test_skip_whitespace("Carriage returns", cr_test, "x");
        test_skip_whitespace("Mixed whitespace", mixed_test, "x");
    }

    /* Test 12: Test all three variants produce same result */
    printf("--- Test 12: Comparing Variants ---\n");
    const char *test_strings[] = {
        "  hello",
        "\t\tworld",
        "no whitespace",
        "  \n  \t",
        ""
    };

    for (int i = 0; i < 5; ++i) {
        char *r1 = skip_whitespace(test_strings[i]);
        char *r2 = skip_whitespace_manual(test_strings[i]);
        char *r3 = skip_whitespace_compact(test_strings[i]);

        int pass = (r1 == r2 && r2 == r3);

        printf("Test string %d: %s\n", i + 1, pass ? "PASS" : "FAIL");
        if (!pass) {
            printf("  skip_whitespace:        points to '%c' (offset %ld)\n",
                   r1 ? *r1 : '?', r1 ? r1 - test_strings[i] : -1);
            printf("  skip_whitespace_manual: points to '%c' (offset %ld)\n",
                   r2 ? *r2 : '?', r2 ? r2 - test_strings[i] : -1);
            printf("  skip_whitespace_compact: points to '%c' (offset %ld)\n",
                   r3 ? *r3 : '?', r3 ? r3 - test_strings[i] : -1);
        }
        tests_run++;
        if (pass) tests_passed++;
    }
    printf("\n");

    /* Test 13: Demonstrating pointer arithmetic */
    printf("--- Test 13: Pointer Arithmetic ---\n");
    {
        const char *str = "   ABC";
        char *first_nonwhite = skip_whitespace(str);

        printf("Original string: \"");
        print_string_visible_whitespace(str);
        printf("\"\n");

        printf("Distance from start: %ld bytes\n",
               first_nonwhite - str);

        printf("Character at returned pointer: '%c'\n", *first_nonwhite);

        printf("Can access subsequent chars: '%c', '%c'\n",
               *(first_nonwhite + 1), *(first_nonwhite + 2));

        tests_run++;
        if ((first_nonwhite - str) == 3 && *first_nonwhite == 'A') {
            tests_passed++;
            printf("Result: PASS\n\n");
        } else {
            printf("Result: FAIL\n\n");
        }
    }

    /* Summary */
    printf("=== Test Summary ===\n");
    printf("Passed: %d / %d tests\n", tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
