#include <cstdio>
#include "logger.h"

void generate(int K, int N, int trace, int i, int j, int* array) {
  if (trace == N) {
    for (; i <= N; ++i) {
      printf("%i", *(array + i - 1));
    }
    printf("\n");
  } else {
    for (; j <= K; ++j) {
      ++trace;
      *(array + trace) = j;
      generate(K, N, trace, 1, 1, array);
      --trace;
    }
  }
}

void printArrangements(int K, int N) {
  int* array = new int[N];
  for (int i = 0; i < N; ++i) {
    array[i] = i + 1;
  }
  generate(K, N, -1, 1, 1, array);
  delete [] array;
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Statements 4");

  int K, N;
  scanf("%i %i", &K, &N);
  INF("A(%i, %i): ", K, N);  // N - length of sequences 1..K
  printArrangements(K, N);

  DBG("[Lesson 1]: Statements 4 [END]");
  return 0;
}

