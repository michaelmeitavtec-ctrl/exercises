/** O'Reilly-C Programming
Exercise 9 -1: Write a procedure that counts the number of words in a string. (Your
documentation should describe exactly how you define a word.) Write a program to
test your new procedure.
*/ 

#include <stdio.h> 
#include <ctype.h> 
#include <stdbool.h> 
 
/** 
 * @brief Counts the number of words in a null-terminated string. 
 * 
 * Definition of a word: 
 *   A word is a maximal contiguous sequence of non-whitespace characters. 
 *   Whitespace is anything isspace() considers whitespace: space, tab 
 *   ('\t'), newline ('\n'), carriage return ('\r'), vertical tab ('\v'), 
 *   and form feed ('\f'). 
 * 
 *   Leading, trailing, and repeated whitespace are ignored/collapsed — 
 *   they never produce empty words. Punctuation and hyphens are treated 
 *   as ordinary word characters (e.g. "well-known," counts as one word). 
 * 
 * @param str Pointer to a null-terminated input string. May be NULL. 
 * @return Number of words in str, or 0 if str is NULL or contains no 
 *         non-whitespace characters. 
 */ 
int count_words(const char *str) 
{ 
    if (str == NULL) { 
        return 0; 
    } 
 
    int word_count = 0; 
    bool in_word = false; 
 
    for (; *str != '\0'; str++) { 
        /* Cast to unsigned char: isspace() has undefined behavior if 
         * given a negative value that isn't EOF, which can happen with 
         * plain `char` on platforms where char is signed and the byte 
         * is >= 0x80 (e.g. UTF-8 continuation bytes). */ 
        if (isspace((unsigned char)*str)) { 
            in_word = false; 
        } else if (!in_word) { 
            in_word = true; 
            word_count++; 
        } 
    } 
 
    return word_count; 
} 
 
/* ---------------------- Test Harness ---------------------- */ 
 
static int tests_run = 0; 
static int tests_passed = 0; 
 
void test_count_words(const char *input, int expected) 
{ 
    int result = count_words(input); 
    tests_run++; 
 
    /* Format string output cleanly for NULL vs non-NULL inputs */ 
    if (input != NULL) { 
        printf("Input   : \"%s\"\n", input); 
    } else { 
        printf("Input   : (null)\n"); 
    } 
 
    printf("Result  : %d word(s)  (Expected: %d)  -> %s\n", 
           result, expected, (result == expected) ? "PASS" : "FAIL"); 
    printf("----------------------------------------------------\n"); 
 
    if (result == expected) { 
        tests_passed++; 
    } 
} 
 
int main(void) 
{ 
    printf("=== Word Counter Test Suite ===\n\n"); 
 
    test_count_words(NULL,                                     0); 
    test_count_words("",                                       0); 
    test_count_words("   ",                                    0); 
    test_count_words("hello",                                  1); 
    test_count_words("hello world",                             2); 
    test_count_words("  Leading and trailing spaces  ",         4); 
    test_count_words("Multiple   spaces\tand\nnewlines",        4); 
    test_count_words("one\ttwo\nthree\rfour\vfive\fsix",        6); 
    test_count_words("single-word-with-hyphens",                1); 
    test_count_words("Punctuation-separated, words count!",     4); 
    test_count_words("a b c d e",                               5); 
    test_count_words("   \t\n\r\v\f   ",                        0); 
 
    /* Test Run Summary */ 
    printf("\nTest Summary: %d / %d tests passed.\n", tests_passed, tests_run); 
 
    return (tests_passed == tests_run) ? 0 : 1; 
}
