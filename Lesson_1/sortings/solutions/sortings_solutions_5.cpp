#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "logger.h"

/* Sortings */
//-----------------------------------------------------------------------------
namespace sort {

/* Insertion sort */
// ----------------------------------------------
void insertion(int array[], size_t size) {
  for (size_t j = 1; j < size; ++j) {
    int key = array[j];
    int i = j - 1;
    while (i >= 0 && array[i] > key) {
      array[i + 1] = array[i];
      --i;
    }
    array[i + 1] = key;
  }
}

/* Merge sort */
// ----------------------------------------------
void merge(int left[], int right[], size_t l, size_t r, int output[]) {
  size_t k = 0;
  while (l > 0 && r > 0) {
    if (*left < *right) {
      output[k] = *left;
      ++left;
      --l;
    } else {
      output[k] = *right;
      ++right;
      --r;
    }
    ++k;
  }

  if (l == 0) {
    for (size_t i = 0; i < r; ++i) {
      output[k++] = *(right++);
    }
  }

  if (r == 0) {
    for (size_t i = 0; i < l; ++i) {
      output[k++] = *(left++);
    }
  }
}

void mergesort(int array[], size_t size) {
  if (size < 2) {
    return;
  }

  size_t left_size = size / 2;
  int* left = new int[left_size];
  for (size_t i = 0; i < left_size; ++i) {
     left[i] = array[i];
  }

  size_t right_size = size - size / 2;
  int* right = new int[right_size];
  for (size_t i = 0; i < right_size; ++i) {
    right[i] = array[i + left_size];
  }

  mergesort(left, left_size);
  mergesort(right, right_size);
  merge(left, right, left_size, right_size, array);

  delete [] left;
  delete [] right;
}

/* Quick sort */
// ----------------------------------------------
size_t partition(int array[], size_t p, size_t r) {
  int pivot = array[r - 1];
  size_t i = p;

  for (size_t j = p + 1; j < r; ++j) {
    if (array[j - 1] <= pivot) {
      ++i;
      std::swap(array[i - 1], array[j - 1]);
    }
  }
  std::swap(array[i], array[r - 1]);
  return i;
}

void quicksort(int array[], size_t p, size_t r) {
  if (p < r) {
    size_t q = partition(array, p, r);
    quicksort(array, p, q);
    quicksort(array, q + 1, r);
  }
}

void quicksort(int array[], size_t size) {
  quicksort(array, 0, size);
}

}  // end namespace sort

/* Strategy */
//-----------------------------------------------------------------------------
typedef void (*Sort)(int array[], size_t size);

void sorting(int array[], size_t size, Sort strategy) {
  strategy(array, size);
}

// ----------------------------------------------
void print(int array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%i ", array[i]);
  }
  printf("\n");
}

void copy(int array[], size_t size, int dest[]) {
  for (size_t i = 0; i < size; ++i) {
    dest[i] = array[i];
  }
}

void performanceTest() {
  clock_t start = clock();
  clock_t elapsed = start;

  while ((elapsed - start) < 5 * CLOCKS_PER_SEC) {
    size_t size = rand() % 10000 + 1000;

    int* A = new int[size];
    int* B = new int[size];
    int* C = new int[size];

    for (size_t i = 0; i < size; ++i) {
      int value = rand() % 1000;
      A[i] = B[i] = C[i] = value;
    }

    clock_t sort_start = clock();
    sorting(A, size, sort::insertion);
    clock_t insertion_elapsed = clock();
    sorting(B, size, sort::mergesort);
    clock_t mergesort_elapsed = clock();
    sorting(C, size, sort::quicksort);
    clock_t quicksort_elapsed = clock();

    delete [] A;  A = nullptr;
    delete [] B;  B = nullptr;
    delete [] C;  C = nullptr;

    double insertion_time = static_cast<double>(insertion_elapsed - sort_start) / CLOCKS_PER_SEC;
    double mergesort_time = static_cast<double>(mergesort_elapsed - insertion_elapsed) / CLOCKS_PER_SEC;
    double quicksort_time = static_cast<double>(quicksort_elapsed - mergesort_elapsed) / CLOCKS_PER_SEC;
    INF("SORT: size [%zu], insertion [%.6lf], merge [%.6lf], quick [%.6lf]", size, insertion_time, mergesort_time, quicksort_time);

    elapsed = clock();
  }
}

/* Main */
//-----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 1]: Sortings: Solutions 5");
  performanceTest();
  DBG("[Lesson 1]: Sortings: Solutions 5 [END]");
  return 0;
}

