#include <stdio.h>
#include <omp.h>
#include <windows.h>

int main() {
    int thread_count = 4; // Number of threads to use
    LARGE_INTEGER frequency, start, end, work_start, work_end;
    double creation_time, work_time, termination_time;

    QueryPerformanceFrequency(&frequency);
    
    QueryPerformanceCounter(&start); // Start time

    #pragma omp parallel num_threads(thread_count)
    {
        if (omp_get_thread_num() == 0) {
            // Get the time as soon as the first thread enters the parallel region
            QueryPerformanceCounter(&work_start);
        }

        // Dummy work to prevent optimization out
        double sum = 0;
        for (int i = 0; i < 10000000; ++i) {
            sum += i;
        }
        
        if (omp_get_thread_num() == 0) {
            // Get the time when the first thread is about to finish the work
            QueryPerformanceCounter(&work_end);
        }
    }
    
    QueryPerformanceCounter(&end); // End time

    // Calculate the time intervals
    creation_time = (double)(work_start.QuadPart - start.QuadPart) / frequency.QuadPart;
    work_time = (double)(work_end.QuadPart - work_start.QuadPart) / frequency.QuadPart;
    termination_time = (double)(end.QuadPart - work_end.QuadPart) / frequency.QuadPart;

    // Output the timing information
    printf("Thread creation time: %lf seconds\n", creation_time);
    printf("Work (including synchronization) time: %lf seconds\n", work_time);
    printf("Thread termination time: %lf seconds\n", termination_time);

    return 0;
}