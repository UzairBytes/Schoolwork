#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_image(int num_rows, int num_cols, 
                int arr[num_rows][num_cols], FILE *fp);
                
void print_image(int num_rows, int num_cols, int arr[num_rows][num_cols]); 

// Remember to include the function prototype for count_cells
int count_cells(int num_rows, int num_cols, int arr[num_rows][num_cols]);

int main(int argc, char **argv) {
    // Print a message to stderr and exit with an argument of 1 if there are
    // not the right number of parameters, or the second argument is not -p
    if ((argc != 3 && argc != 2) || (argc == 3 && strcmp(argv[2], "-p") != 0)) {
        fprintf(stderr, "Usage: count_cells <imagefile.txt> [-p]\n");
        exit(1);
    }
    if (argc == 2){
        int i, j;
        FILE* fp = fopen(argv[1], "r");
        if (fp == NULL){
            fprintf(stderr, "FILE NOT FOUND\n");
            exit(1);
        }
        fscanf(fp, "%d %d", &i, &j);
        int arr[i][j];
        read_image(i, j, arr, fp);
        int num_cells = count_cells(i, j, arr);
        printf("Number of Cells is %d\n", num_cells);
    }
    else{
        int i, j;
        FILE* fp = fopen(argv[1], "r");
        if (fp == NULL){
            fprintf(stderr, "FILE NOT FOUND\n");
            exit(1);
        }
        fscanf(fp, "%d %d", &i, &j);
        int arr[i][j];
        read_image(i, j, arr, fp);
        int num_cells = count_cells(i, j, arr);
        print_image(i, j, arr);
        printf("Number of Cells is %d\n", num_cells);
    }
    return 0;
}