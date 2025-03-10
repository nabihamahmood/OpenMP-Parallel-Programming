#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 500  // Matrix size
#define CHUNK_SIZE 100  // Chunk size for scheduling

// Function to multiply matrices using OpenMP with dynamic scheduling
void multiplyDynamic(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE], int threads) {
    int i, j, k; // Loop variables

    // Parallel multiplication using OpenMP with dynamic scheduling
    #pragma omp parallel for num_threads(threads) schedule(dynamic, CHUNK_SIZE) private(i, j, k) shared(A, B, C)
    for (i = 0; i < SIZE; i++) {  
        for (j = 0; j < SIZE; j++) {  
            C[i][j] = 0;  
            for (k = 0; k < SIZE; k++) {  
                C[i][j] += A[i][k] * B[k][j];  
            }
        }
    }
}

int main() {
    int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE]; // Matrices
    srand(42); // Set random seed

    // Fill matrices A and B with random numbers
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand() % 100;  // Random number 0-99
            B[i][j] = rand() % 100;  // Random number 0-99
        }
    }

    int threadOptions[] = {1, 4, 8}; // Test with 1, 4, and 8 threads

    printf("\n==== Running with Dynamic Scheduling ====\n");
    for (int t = 0; t < 3; t++) {
        int threads = threadOptions[t];
        printf("\nUsing %d threads (Dynamic Scheduling)\n", threads);

        double totalTime = 0;  

        for (int run = 0; run < 10; run++) {  
            double start = omp_get_wtime();  
            multiplyDynamic(A, B, C, threads);  
            double end = omp_get_wtime();  

            double timeTaken = end - start;  
            totalTime += timeTaken;  

            printf("Run %d -> Threads: %d  Time: %f sec\n", run + 1, threads, timeTaken);
        }

        double avgTime = totalTime / 10;  
        printf("Average time with %d threads (Dynamic): %f sec\n", threads, avgTime);
    }

    return 0;  
}
