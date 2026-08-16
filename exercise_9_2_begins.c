/**
Exercise 9-2: Write a function begins(string1,string2) that returns true if
string1 begins string2. Write a program to test the function.#include <stdio.h>
#include <stdbool.h>
*/
/**
 * @brief Determines whether string1 begins with string2.
 *
 * Definition:
 *   string1 begins string2 if every character in string2
 *   matches the corresponding character at the beginning
 *   of string1.
 *
 *   The comparison is case-sensitive.
 *   The empty string is considered to be a prefix of every string.
 *
 * Examples:
 *   begins("Hello world", "Hello") -> true
 *   begins("Hello world", "Hell")  -> true
 *   begins("Hello world", "hello") -> false
 *   begins("Hello", "Hello world") -> false
 *
 * @param string1 The string to be tested.
 * @param string2 The proposed prefix.
 * @return true if string1 begins with string2, otherwise false.
 */
bool begins(const char *string1, const char *string2)
{
    if (string1 == NULL || string2 == NULL) {
        return false;
    }

    while (*string2 != '\0') {
        if (*string1 == '\0' || *string1 != *string2) {
            return false;
        }

        string1++;
        string2++;
    }

    return true;
}

/* ---------------------- Test Harness ---------------------- */

static int tests_run = 0;
static int tests_passed = 0;

void test_begins(const char *string1,
                 const char *string2,
                 bool expected)
{
    bool result = begins(string1, string2);
    tests_run++;

    printf("string1 : \"%s\"\n", string1);
    printf("string2 : \"%s\"\n", string2);
    printf("Result  : %s (Expected: %s) -> %s\n",
           result ? "true" : "false",
           expected ? "true" : "false",
           result == expected ? "PASS" : "FAIL");
    printf("----------------------------------------------\n");

    if (result == expected) {
        tests_passed++;
    }
}

int main(void)
{
    printf("=== begins() Test Suite ===\n\n");

    test_begins("Hello world", "Hello", true);
    test_begins("Hello world", "Hell", true);
    test_begins("Hello world", "Hello world", true);
    test_begins("Hello world", "hello", false);
    test_begins("Hello world", "world", false);
    test_begins("Hello", "Hello world", false);
    test_begins("", "", true);
    test_begins("Hello", "", true);
    test_begins("", "Hello", false);
    test_begins("abcde", "abc", true);
    test_begins("abcde", "abd", false);
    test_begins("abc", "abcd", false);

    printf("\nTest Summary: %d / %d tests passed.\n",
           tests_passed, tests_run);

    return (tests_passed == tests_run) ? 0 : 1;
}
