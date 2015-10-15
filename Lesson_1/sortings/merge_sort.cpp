#include "logger.h"

namespace sort {

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

}

void print(int array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%i ", array[i]);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Sortings: Merge sort");

  int array[10] = {5, 8, 1, 12, -4, -7, 3, 5, 9, 0};
  print(array, 10);
  INF("After sorting");
  sort::mergesort(array, 10);
  print(array, 10);

  DBG("[Lesson 1]: Sortings: Merge sort [END]");
  return 0;
}

