#include <cstdlib>
#include <ctime>
#include "logger.h"

/* Binary search */
// ----------------------------------------------------------------------------
int binarySearch(int x, int array[], size_t size) {
  size_t l = 0;
  size_t r = size;

  if (size == 0 || array[0] > x || array[r - 1] < x) {
    return -1;
  }

  while (l < r) {
    size_t m = l + (r - l) / 2;
    if (x <= array[m]) {
      r = m;
    } else {
      l = m + 1;
    }
  }

  if (array[r] == x) {
    return r;
  }
  return -1;
}

/* Unit test */
// ----------------------------------------------
int compare(const void* a, const void* b){ 
  return (*static_cast<const int*>(a) - *static_cast<const int*>(b));
}

void print(int array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%i ", array[i]);
  }
  printf("\n");
}

void unitTest() {  // good case: 4 22 35 71 86 87 97 97 97   [expected = 7, actual = 6]
  clock_t start = clock();
  clock_t elapsed = start;
  bool flag = true;

  while (flag && (elapsed - start) < 5 * CLOCKS_PER_SEC) {
    size_t size = rand() % 65536 + 1000;  // 10 + 1;
    int* array = new int[size];

    for (size_t i = 0; i < size; ++i) {
      array[i] = rand() % 100;
    }
    qsort(array, size, sizeof(int), compare);

    int x = rand() % 100;
    int* ptr = static_cast<int*>(bsearch(&x, array, size, sizeof(int), compare));
    int expected = ptr != nullptr ? ptr - array : -1;
    int actual = binarySearch(x, array, size);

    if (expected >= 0 && actual >= 0 && expected != actual) {
      WRN("Found: x = %i, expected = %i, actual = %i", x, expected, actual);
      // print(array, size);
      // flag = false;
    } else if (expected == actual) {
      INF("OK: %zu", size);
    } else {
      ERR("Error: x = %i, expected = %i, actual = %i", x, expected, actual);
      print(array, size);
      flag = false;
    }

    delete [] array;  array = nullptr;
    elapsed = clock();
  }
}

/* Main */
//-----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 1]: Sortings: Binary search");
  unitTest();
  DBG("[Lesson 1]: Sortings: Binary search [END]");
  return 0;
}

