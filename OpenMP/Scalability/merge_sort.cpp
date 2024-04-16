#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

#define MAX_SIZE 100

void merge(int *input_array, int n, int *arr) {
   int i = 0;
   int j = n/2;
   int k = 0;

   while (i < n/2 && j < n) {
      if (input_array[i] < input_array[j]) {
         arr[k] = input_array[i];
         i += 1;
      } else {
         arr[k] = input_array[j];
         j += 1;
      }
      k += 1;
   }

   while (i < n/2) {
      arr[k] = input_array[i];
      i += 1;
      k += 1;
   }
   while (j<n) {
      arr[k] = input_array[j];
      j += 1;
      k += 1;
   }

   memcpy(input_array, arr, n*sizeof(int));
}

void mergeSort(int *input_array, int n, int *extra_array)
{
   if (n < 2) {
      return;
   }
   
   #pragma omp task shared(input_array) if (n > MAX_SIZE)
   mergeSort(input_array, n/2, extra_array);

   #pragma omp task shared(input_array) if (n > MAX_SIZE)
   mergeSort(input_array+(n/2), n-(n/2), extra_array + n/2);

   #pragma omp taskwait
   merge(input_array, n, extra_array);
}

int main(int argc, char *argv[]) {
   int n  = (argc > 1) ? atoi(argv[1]) : 10;
   int num_threads = atoi(argv[2]);
   int *input_array = (int *)malloc(n * sizeof(int));
   int *extra_array = (int *)malloc(n * sizeof(int));

   omp_set_dynamic(0);
   omp_set_num_threads(num_threads);

   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> dis(1, 100);
   for(int i=0; i<n; i++){
      input_array[i] = dis(gen);
   }

   auto start = std::chrono::high_resolution_clock::now();
   #pragma omp parallel
   {
      #pragma omp single
      mergeSort(input_array, n, extra_array);
   }
   auto end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = end - start;
   std::cout << "Elapsed time: " << elapsed.count() * 1000000 << " micro seconds" << std::endl;

   free(input_array);
   free(extra_array);
   return 0;
}