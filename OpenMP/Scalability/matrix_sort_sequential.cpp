#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <chrono>

using namespace std;

int main() {
    std::vector<std::vector<int>> matrix = {
        {3, 2, 1},
        {6, 5, 4},
        {9, 8, 7}
    };

    std::vector<int> linear_matrix_vector;
    int matrix_length = matrix.size();

    for (int i = 0; i <= matrix_length - 1; ++i) {
        for (int j = 0; j <= matrix_length - 1; ++j) {
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

    for (int i = 0; i <= matrix_length - 1; ++i) {
        for (int j = 0; j <= matrix_length - 1; ++j) {
            {
                matrix[i][j] = linear_matrix_vector[k];
                k += 1;
            }
        }
    }

    std::cout << "Sorted Matrix:" << std::endl;
    for (int i = 0; i <= matrix_length - 1; ++i) {
        for (int j = 0; j <= matrix_length - 1; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
