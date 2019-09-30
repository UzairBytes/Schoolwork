#include <stdio.h>
#include <stdlib.h>

/* Return a pointer to an array of two dynamically allocated arrays of ints.
   The first array contains the elements of the input array s that are
   at even indices.  The second array contains the elements of the input
   array s that are at odd indices.

   Do not allocate any more memory than necessary.
*/
int **split_array(const int *s, int length) {
    int num_even;
    int num_odd = length / 2;
    if (length % 2 == 0){
        num_even = length / 2;
    }
    else{
        num_even = length / 2 + 1;
    }
    int** new_array = malloc(sizeof(int*) * 2);
    new_array[0] = malloc(sizeof(int) * num_even);
    new_array[1] = malloc(sizeof(int) * num_odd);

    int next_even = 0;
    int j = 0;
    int k = 0;
    for (int x = 0; x < length; x++){
        if (next_even == 0) {
            new_array[0][j] = s[x];
            j++;
            next_even = 1;
        }
        else{
            new_array[1][k] = s[x];
            k++;
            next_even = 0;
        }
    }
    return new_array;
}

/* Return a pointer to an array of ints with size elements.
   - strs is an array of strings where each element is the string
     representation of an integer.
   - size is the size of the array
 */

int *build_array(char **strs, int size) {
    int* new_array;
    new_array = malloc(sizeof(int) * size);
    char* endptr;

    for (int x = 0; x < size; x++){
        new_array[x] = strtol(strs[x], &endptr, 10);
    }

    return new_array;


}


int main(int argc, char **argv) {
    /* Replace the comments in the next two lines with the appropriate
       arguments.  Do not add any additional lines of code to the main
       function or make other changes.
     */
    int *full_array = build_array(&argv[1], argc - 1);
    int **result = split_array(full_array, argc - 1);

    printf("Original array:\n");
    for (int i = 0; i < argc - 1; i++) {
        printf("%d ", full_array[i]);
    }
    printf("\n");

    printf("result[0]:\n");
    for (int i = 0; i < argc/2; i++) {
        printf("%d ", result[0][i]);
    }
    printf("\n");

    printf("result[1]:\n");
    for (int i = 0; i < (argc - 1)/2; i++) {
        printf("%d ", result[1][i]);
    }
    printf("\n");
    free(full_array);
    free(result[0]);
    free(result[1]);
    free(result);
    return 0;
}
