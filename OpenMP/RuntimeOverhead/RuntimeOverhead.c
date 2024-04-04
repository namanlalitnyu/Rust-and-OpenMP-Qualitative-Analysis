#include <stdio.h>
#include <omp.h>
#include <windows.h>

int main() {
    int thread_count = 4; // Number of threads to use
    LARGE_INTEGER frequency, start, end, sync_start, sync_end;
    double creation_time, sync_time, termination_time;

    QueryPerformanceFrequency(&frequency);
    
    QueryPerformanceCounter(&start); // Start time

    #pragma omp parallel num_threads(thread_count)
    {
        // Dummy work to prevent optimization out before synchronization
        double pre_sum = 0;
        for (int i = 0; i < 100000; ++i) {
            pre_sum += i;
        }

        int thread_num = omp_get_thread_num();
        if (thread_num == 0) {
            // Get the time before synchronization (only by the master thread)
            QueryPerformanceCounter(&sync_start);
        }

        // Synchronization point: all threads wait here
        #pragma omp barrier
        
        if (thread_num == 0) {
            // Get the time after synchronization (only by the master thread)
            QueryPerformanceCounter(&sync_end);
        }

        // Dummy work to prevent optimization out after synchronization
        double post_sum = 0;
        for (int i = 0; i < 100000; ++i) {
            post_sum += i;
        }
    }
    
    QueryPerformanceCounter(&end); // End time

    // Calculate the time intervals
    creation_time = (double)(sync_start.QuadPart - start.QuadPart) / frequency.QuadPart;
    sync_time = (double)(sync_end.QuadPart - sync_start.QuadPart) / frequency.QuadPart;
    termination_time = (double)(end.QuadPart - sync_end.QuadPart) / frequency.QuadPart;

    // Output the timing information
    printf("Thread creation time: %lf seconds\n", creation_time);
    printf("Synchronization time: %lf seconds\n", sync_time);
    printf("Thread termination time: %lf seconds\n", termination_time);

    return 0;
}
