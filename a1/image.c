#include <stdio.h>
    
/* Reads the image from the open file fp into the two-dimensional array arr 
 * num_rows and num_cols specify the dimensions of arr
 */
void read_image(int num_rows, int num_cols, 
                int arr[num_rows][num_cols], FILE *fp) {
    for (int x = 0; x < num_rows; x++){
        for (int y = 0; y < num_cols; y++){
            fscanf(fp, "%d", &arr[x][y]);
        }
    }
}

/* Print to standard output the contents of the array arr */
void print_image(int num_rows, int num_cols, int arr[num_rows][num_cols]) {
    for (int x = 0; x < num_rows; x++){
        for (int y = 0; y < num_cols; y++){
            printf("%d ", arr[x][y]);
        }
        printf("\n");
    }
}

void eliminate_cell(int x, int y, int num_rows, int num_cols, int arr[num_rows][num_cols]){
    arr[x][y]=0;
    
    if (x-1>= 0 && arr[x-1][y] != 0){
        eliminate_cell(x-1, y, num_rows, num_cols, arr);
    }
    if (x+1 < num_rows && arr[x+1][y]!=0){
        eliminate_cell(x+1, y, num_rows, num_cols, arr);
    }
    if (y-1 >= 0 && arr[x][y-1] != 0){
        eliminate_cell(x, y-1, num_rows, num_cols, arr);
    }
    if (y+1 < num_cols && arr[x][y+1] != 0){
        eliminate_cell(x, y+1, num_rows, num_cols, arr);
    }
}

/* TODO: Write the count_cells function */
int count_cells(int num_rows, int num_cols, int arr[num_rows][num_cols]) {
    // Count the number of cells by looking for the one pixel of the cell that
    // has no  non-zero pixel around it.
    int num_cells = 0;
    for (int row = 0; row < num_rows; row++){
        for (int col = 0; col < num_cols; col++){
            if (arr[row][col] == 255){
                eliminate_cell(row, col, num_rows, num_cols, arr);
                num_cells++;
                }
        }
    }
    return num_cells;
}

