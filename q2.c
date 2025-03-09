#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define ROWS 1000  
#define COLS 1000  
#define NUM_RUNS 10  

int main() {
    int arr[ROWS][COLS]; // Declare a 2D array

    // Fill the 2D array with random values
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            arr[i][j] = rand() % 1000000; // Assign random values to array elements
        }
    }
