#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000  // Matrix size

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE]; // Declare matrices globally to avoid stack overflow issues

// Function to fill matrices with random values
void fill_matrices() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand() % 10;  // Random values between 0-9
            B[i][j] = rand() % 10;
            C[i][j] = 0;  // Initialize result matrix to 0
        }
    }
}

// Function for sequential matrix multiplication
void multiply() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < SIZE; k++) {
                sum += A[i][k] * B[k][j];  // Multiply and sum up
            }
            C[i][j] = sum;
        }
    }
}

int main() {
    fill_matrices();  // Fill matrices with random values

    printf("== Running Sequential Multiplication ==\n");

    double total_time = 0;  // Store total execution time for averaging

    for (int r = 0; r < 10; r++) {  // Run 10 times
        clock_t start = clock();  // Start time
        multiply();
        clock_t end = clock();  // End time
        
        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;  // Convert to seconds
        total_time += time_taken;

        printf("Run %d Time: %.6f sec\n", r + 1, time_taken);
    }

    printf("Average Time: %.6f sec\n", total_time / 10);  // Print average execution time

    return 0;
}
