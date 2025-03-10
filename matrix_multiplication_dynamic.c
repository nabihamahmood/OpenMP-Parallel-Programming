#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000   // Size of the matrices (1000x1000)
#define CHUNK 250   // Chunk size 

// Declaring matrices globally to prevent stack overflow issues
int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE]; 

// Function to fill matrices A and B with random numbers and set C to zero
void fillMatrices() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand() % 10;  // Fill matrix A with random numbers (0-9)
            B[i][j] = rand() % 10;  // Fill matrix B with random numbers (0-9)
            C[i][j] = 0;            // Initialize matrix C with zeros
        }
    }
}

// Function to multiply matrices using OpenMP with dynamic scheduling
void multiplyDynamic(int threads) {
    #pragma omp parallel for num_threads(threads) schedule(dynamic, CHUNK)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < SIZE; k++) {
                sum += A[i][k] * B[k][j];  // Multiply and calculate the sum
            }
            C[i][j] = sum;  // Store the result in matrix C
        }
    }
}

int main() {
    fillMatrices(); 

    int threadOptions[] = {1, 4, 8};  // Test with 1, 4, and 8 threads

    printf("Running with Dynamic Scheduling:\n");

    for (int t = 0; t < 3; t++) {
        int threads = threadOptions[t];  
        printf("\nUsing %d threads (Dynamic Scheduling)\n", threads);

        double totalTime = 0;  // Keep track of total execution time

        // Run the multiplication 10 times to get an average time
        for (int run = 0; run < 10; run++) {  
            double start = omp_get_wtime();  // Start timer
            multiplyDynamic(threads);  // Multiply matrices
            double end = omp_get_wtime();  // Stop timer
            
            double executionTime = end - start;
            totalTime += executionTime;  // Add to total time

            printf("Run %d Time: %.6f sec\n", run + 1, executionTime);
        }

        // Print the average execution time over 10 runs
        printf("Average Time: %.6f sec\n", totalTime / 10);
    }

    return 0;
}
