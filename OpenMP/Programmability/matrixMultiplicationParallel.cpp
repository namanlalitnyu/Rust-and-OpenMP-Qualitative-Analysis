#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <chrono>
#include <stdlib.h>
#include <random>

using namespace std;

vector<vector<int>> matrix_multiplication(vector<vector<int>> A, vector<vector<int>> B, int matrix_size, int num_threads){
    vector<vector<int>> C(matrix_size, vector<int>(matrix_size));

    #pragma omp parallel for num_threads(num_threads)
    for (int i=0; i<matrix_size; i++) {
        for (int j=0; j <matrix_size; j++) {
            for (int k=0; k<matrix_size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int main(int argc, char *argv[]){
    int matrix_size = atoi(argv[1]);
    int num_threads = atoi(argv[2]);

    vector<vector<int>> A(matrix_size, vector<int>(matrix_size));
    vector<vector<int>> B(matrix_size, vector<int>(matrix_size));
    vector<vector<int>> C(matrix_size, vector<int>(matrix_size));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);

    for(int i=0;i<matrix_size;i++){
        for(int j=0;j<matrix_size;j++){
            A[i][j] = dis(gen);
            B[i][j] = dis(gen);
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    C = matrix_multiplication(A, B, matrix_size, num_threads);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() * 1000000 << " micro seconds" << std::endl;
    return 0;
}