#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <chrono>

using namespace std;

int main() {
    std::vector<std::vector<int>> matrix = {
        {144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133},
        {121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110},
        {100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89},
        {81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70},
        {64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53},
        {49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38},
        {36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25},
        {25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14},
        {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5},
        {9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 11, 12},
        {4, 3, 2, 1, 5, 6, 7, 8, 9, 10, 11, 12},
        {13, 14, 11, 12, 10, 15, 18, 17, 16, 19, 20, 21}
    };

    std::vector<int> linear_matrix_vector;
    int matrix_length = matrix.size();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i <= matrix_length - 1; ++i) {
        for (int j = 0; j <= matrix_length - 1; ++j) {
            #pragma omp critical
            {
                linear_matrix_vector.push_back(matrix[i][j]);
            }
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::sort(linear_matrix_vector.begin(), linear_matrix_vector.end());
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() * 1000000 << " micro seconds" << std::endl;
    
    int k = 0;

    #pragma omp parallel for collapse(2)
    for (int i = 0; i <= matrix_length - 1; ++i) {
        for (int j = 0; j <= matrix_length - 1; ++j) {
            #pragma omp critical
            {
                matrix[i][j] = linear_matrix_vector[k];
                k += 1;
            }
        }
    }

    // std::cout << "Sorted Matrix:" << std::endl;
    // for (int i = 0; i <= matrix_length - 1; ++i) {
    //     for (int j = 0; j <= matrix_length - 1; ++j) {
    //         std::cout << matrix[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}
