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
double totalTimeStatic = 0.0; // Variable to store total execution time for static scheduling

// Static Scheduling Execution
for (int i = 0; i < NUM_RUNS; ++i) {
    clock_t start = clock(); // Start time measurement
    int maxElement = findMaxParallel(arr, 's'); // Find max using static scheduling
    clock_t end = clock(); // End time measurement

    double duration = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0; // Convert to ms
    totalTimeStatic += duration;

    printf("Static Run %d: Max = %d, Time = %.3f ms\n", i + 1, maxElement, duration);
}

printf("Average Static Execution Time: %.3f ms\n", totalTimeStatic / NUM_RUNS);
