/*
Example 13-4 counts the number of elements that are nonzero and stops when a
zero is found. No limit check is provided, so there must be at least one zero in the
array.
*/

#include <stdio.h>

int array[] = {4, 5, 8, 9, 8, 1, 0, 1, 9, 3};
int array_index;

int main(void)
{
    array_index = 0;
    while (array[array_index] != 0) {
        ++array_index;
    }
    
    printf("Number of elements before zero %d\n", array_index);
    return 0;
}
