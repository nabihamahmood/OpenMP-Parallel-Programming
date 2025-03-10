#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 500  // Matrix size

// Function to multiply matrices sequentially (no parallelism)
void multiplySequential(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {  // Loop through each row of A
        for (int j = 0; j < SIZE; j++) {  // Loop through each column of B
            C[i][j] = 0;  // Initialize result matrix C[i][j]
            for (int k = 0; k < SIZE; k++) {  // Multiply corresponding elements
                C[i][j] += A[i][k] * B[k][j];  // Store result in C
            }
        }
    }
}

int main() {
    int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE]; // Matrices
    srand(42); // Seed for random numbers

    // Fill matrices A and B with random numbers
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand() % 100;  // Random number 0-99
            B[i][j] = rand() % 100;  // Random number 0-99
        }
    }

    double totalTime = 0;  

    printf("\n==== Running Sequential Multiplication ====\n");
    for (int run = 0; run < 10; run++) {  // Run 10 times to get an average
        clock_t start = clock();  // Start time measurement
        multiplySequential(A, B, C);  // Perform matrix multiplication
        clock_t end = clock();  // End time measurement

        double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;  // Convert to seconds
        totalTime += timeTaken;  

        printf("Run %d Time: %f sec\n", run + 1, timeTaken);  // Print time taken
    }

    double avgTime = totalTime / 10;  // Compute average time
    printf("Average Sequential Time: %f sec\n", avgTime);  // Print final result

    return 0;
}
