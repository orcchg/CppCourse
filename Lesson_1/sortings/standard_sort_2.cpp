#include <algorithm>
#include <cstdlib>
#include <random>
#include "logger.h"

namespace sort {

/* Quick sort */
// ----------------------------------------------------------------------------
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

/* Merge sort */
// ----------------------------------------------------------------------------
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

/* Insertion sort */
// ----------------------------------------------------------------------------
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

}

/* Utility */
// ----------------------------------------------------------------------------
void print(int array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%i ", array[i]);
  }
  printf("\n");
}

void copy(int source[], int destination[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    *destination++ = *source++;
  }
}

bool equal(int A[], int B[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    if (A[i] != B[i]) {
      return false;
    }
  }
  return true;
}

void generateArray(int array[], size_t size) {
  std::default_random_engine rng;
  std::uniform_int_distribution<int> distribution;

  for (size_t i = 0; i < size; ++i) {
    array[i] = distribution(rng);
  }
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 1]: Sortings: Standard sort 2");

  bool flag = true;

  while (flag) {
    size_t size = std::rand() % 65536 + 1;
    int* A = new int[size];
    int* B = new int[size];
    int* C = new int[size];

    generateArray(A, size);
    copy(A, B, size);
    copy(A, C, size);

    sort::insertion(A, size);
    sort::mergesort(B, size);
    sort::quicksort(C, size);

    bool accumulate_1 = equal(A, B, size);
    bool accumulate_2 = equal(A, C, size);
    bool accumulate_3 = equal(B, C, size);

    if (!accumulate_1) {
      ERR("Insertion vs Mergesort NOT equal result!");
      print(A, size);
      printf("\n");
      print(B, size);
      flag = false;
    }
    if (!accumulate_2) {
      ERR("Insertion vs Quicksort NOT equal result!");
      print(A, size);
      printf("\n");
      print(C, size);
      flag = false;
    }
    if (!accumulate_3) {
      ERR("Mergesort vs Quicksort NOT equal result!");
      print(B, size);
      printf("\n");
      print(C, size);
      flag = false;
    }

    if (flag) {
      INF("OK: %zu", size);
    }

    delete [] A;
    delete [] B;
    delete [] C;
  }

  DBG("[Lesson 1]: Sortings: Standard sort 2 [END]");
  return 0;
}

