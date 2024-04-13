#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

void mergeSortAux(int *X, int n, int *arr) {
   int i = 0;
   int j = n/2;
   int ti = 0;

   while (i < n/2 && j < n) {
      if (X[i] < X[j]) {
         arr[ti] = X[i];
         ti++; i++;
      } else {
         arr[ti] = X[j];
         ti++; j++;
      }
   }
   while (i < n/2) {
      arr[ti] = X[i];
      ti++; i++;
   }
   while (j<n) {
      arr[ti] = X[j];
      ti++; j++;
   }
   memcpy(X, arr, n*sizeof(int));
}

void mergeSort(int *X, int n, int *tmp)
{
   if (n < 2) return;

   mergeSort(X, n/2, tmp);

   mergeSort(X+(n/2), n-(n/2), tmp + n/2);

   mergeSortAux(X, n, tmp);
}

int main(int argc, char *argv[]) {
   int n  = (argc > 1) ? atoi(argv[1]) : 10;
   int *X = (int *)malloc(n * sizeof(int));
   int *tmp = (int *)malloc(n * sizeof(int));

   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> dis(1, 100);
   for(int i=0; i<n; i++){
      X[i] = dis(gen);
   }

   auto start = std::chrono::high_resolution_clock::now();
   mergeSort(X, n, tmp);
   auto end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = end - start;
   std::cout << "Elapsed time: " << elapsed.count() * 1000000 << " micro seconds" << std::endl;

   free(X);
   free(tmp);
   return 0;
}