#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <chrono>

using namespace std;

int main() {
    std::vector<std::vector<int>> matrix = {
        {20, 71, 301, 265, 219, 168, 154, 31, 237, 277, 41, 295, 120, 39, 356, 111, 120, 143, 316, 119},
        {137, 346, 210, 393, 337, 49, 34, 30, 199, 54, 298, 284, 110, 198, 374, 217, 376, 197, 304, 332},
        {237, 69, 320, 307, 65, 87, 54, 170, 394, 182, 44, 171, 198, 101, 329, 81, 209, 317, 271, 135},
        {387, 168, 356, 204, 3, 287, 37, 28, 203, 346, 54, 148, 42, 268, 381, 238, 204, 339, 107, 107},
        {84, 104, 110, 222, 249, 361, 354, 4, 238, 146, 202, 346, 90, 234, 142, 75, 74, 251, 138, 167},
        {186, 371, 17, 288, 274, 111, 316, 280, 372, 265, 304, 392, 136, 150, 245, 173, 152, 36, 116, 291},
        {264, 291, 278, 80, 136, 337, 235, 258, 260, 35, 93, 252, 271, 362, 37, 346, 113, 186, 266, 245},
        {197, 7, 378, 295, 353, 49, 54, 81, 134, 270, 139, 23, 10, 209, 110, 297, 211, 180, 231, 47},
        {56, 305, 239, 33, 340, 342, 188, 274, 298, 140, 97, 326, 207, 243, 83, 280, 83, 294, 45, 104},
        {227, 42, 147, 6, 296, 374, 24, 82, 263, 224, 283, 53, 296, 63, 38, 19, 271, 32, 296, 60},
        {40, 5, 264, 292, 222, 51, 56, 46, 49, 220, 29, 193, 68, 29, 268, 176, 70, 212, 79, 216},
        {87, 101, 97, 236, 338, 219, 19, 76, 154, 366, 244, 289, 92, 236, 29, 274, 221, 307, 376, 377},
        {184, 238, 304, 286, 319, 54, 315, 120, 28, 266, 222, 52, 210, 36, 234, 264, 85, 64, 77, 386},
        {249, 68, 245, 277, 271, 149, 309, 277, 48, 133, 326, 233, 125, 220, 209, 290, 307, 215, 249, 275},
        {382, 346, 14, 119, 107, 374, 75, 54, 231, 8, 312, 96, 364, 259, 303, 319, 180, 242, 184, 267},
        {11, 89, 174, 200, 353, 90, 335, 336, 115, 304, 157, 194, 153, 129, 334, 359, 82, 67, 147, 203},
        {205, 303, 239, 164, 256, 195, 192, 360, 242, 302, 100, 228, 98, 152, 72, 384, 377, 104, 353, 221},
        {365, 195, 280, 211, 284, 360, 105, 44, 227, 171, 182, 116, 257, 128, 111, 186, 341, 270, 378, 333},
        {332, 227, 222, 236, 397, 263, 104, 195, 219, 7, 31, 234, 164, 93, 179, 43, 263, 156, 307, 280},
        {160, 231, 61, 128, 137, 245, 255, 11, 281, 98, 72, 180, 127, 108, 210, 45, 132, 74, 95, 165}
    };

    int matrix_length = matrix.size();
    std::vector<int> linear_matrix_vector(matrix_length*matrix_length);

    #pragma omp parallel for num_threads(5)
    for (int i = 0; i <= matrix_length - 1; i++) {
        for (int j = 0; j <= matrix_length - 1; j++) {
            linear_matrix_vector[(i*matrix_length) + j] = matrix[i][j];
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    // std::sort(linear_matrix_vector.begin(), linear_matrix_vector.end());

     #pragma omp parallel num_threads(5)
    {
        // #pragma omp single nowait
        // {
            std::sort(linear_matrix_vector.begin(), linear_matrix_vector.end());
        // }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() * 1000000 << " micro seconds" << std::endl;
    
    int k = 0;

    #pragma omp parallel for num_threads(5)
    for (int i = 0; i <= matrix_length - 1; i++) {
        for (int j = 0; j <= matrix_length - 1; j++) {
            matrix[i][j] = linear_matrix_vector[(i*matrix_length) + j];
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
