#include <cstdio>
#include <ctime>

int main(int argc, char** argv) {

  clock_t start = clock();
  clock_t elapsed = start;
  int count = 0;

  while (elapsed - start < 0.5 * CLOCKS_PER_SEC) {
    ++count;
    if (count % 100000 == 0) {
      printf("OK\n");
    }
    elapsed = clock();
  }

  return 0;
}


// while (bool expression) { ... }
