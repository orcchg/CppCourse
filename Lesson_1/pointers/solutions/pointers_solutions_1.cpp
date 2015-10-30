#include <cstdio>
#include <cstdlib>
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

/* Main */
//-----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 1]: Pointers: Solutions 1");

  int A[] = {5, 8, -1, 0, 4, 12, 3, -7, 8, 9, 16, 2, -3, -1, 1, 5, -2, 0};
  size_t size = sizeof(A) / sizeof(A[0]);
  int B[size];
  int C[size];

  copy(A, size, B);
  copy(A, size, C);
  print(A, size);

  sorting(A, size, sort::insertion);
  print(A, size);
  sorting(B, size, sort::mergesort);
  print(B, size);
  sorting(C, size, sort::quicksort);
  print(C, size);

  DBG("[Lesson 1]: Pointers: Solutions 1 [END]");
  return 0;
}

