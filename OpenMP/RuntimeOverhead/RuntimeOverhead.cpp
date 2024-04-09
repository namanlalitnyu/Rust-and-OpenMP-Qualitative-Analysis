#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

int main() {
    std::vector<int> threads_to_test = {1, 2, 4, 8, 16};
    int num_iterations = 1000; // Increase the number of iterations to get a measurable duration

    for (int thread_count : threads_to_test) {
        double total_creation_time = 0.0, total_sync_time = 0.0, total_termination_time = 0.0;

        std::cout << "Testing with " << thread_count << " threads:\n";

        for (int iter = 0; iter < num_iterations; ++iter) {
            std::chrono::high_resolution_clock::time_point start, end, sync_start, sync_end;

            start = std::chrono::high_resolution_clock::now();

            #pragma omp parallel num_threads(thread_count)
            {
                if (omp_get_thread_num() == 0) {
                    sync_start = std::chrono::high_resolution_clock::now();
                }

                #pragma omp barrier

                if (omp_get_thread_num() == 0) {
                    sync_end = std::chrono::high_resolution_clock::now();
                }
            }
            
            end = std::chrono::high_resolution_clock::now();

            total_creation_time += std::chrono::duration_cast<std::chrono::nanoseconds>(sync_start - start).count();
            total_sync_time += std::chrono::duration_cast<std::chrono::nanoseconds>(sync_end - sync_start).count();
            total_termination_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - sync_end).count();
        }

        double avg_creation_time = (total_creation_time / num_iterations) / 1e9;
        double avg_sync_time = (total_sync_time / num_iterations) / 1e9;
        double avg_termination_time = (total_termination_time / num_iterations) / 1e9;

        std::cout.precision(9); 
        std::cout << "Average thread creation time: " << avg_creation_time << " seconds\n";
        std::cout << "Average synchronization time: " << avg_sync_time << " seconds\n";
        std::cout << "Average thread termination time: " << avg_termination_time << " seconds\n\n";
    }

    return 0;
}
