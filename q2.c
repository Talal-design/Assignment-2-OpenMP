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
    // Function to find the max element using OpenMP with reduction and scheduling
int findMaxParallel(int arr[ROWS][COLS], char scheduleType) {
    int maxElement = arr[0][0]; // Initialize maxElement with the first element

    // Choose scheduling type
    if (scheduleType == 's') {  // Static scheduling
        #pragma omp parallel for collapse(2) schedule(static) reduction(max : maxElement)
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (arr[i][j] > maxElement) {
                    maxElement = arr[i][j];
                }
            }
        }
    } else {  // Dynamic scheduling
        #pragma omp parallel for collapse(2) schedule(dynamic) reduction(max : maxElement)
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (arr[i][j] > maxElement) {
                    maxElement = arr[i][j];
                }
            }
        }
    }
    return maxElement;
}

