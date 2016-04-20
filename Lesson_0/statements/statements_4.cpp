#include <cstdio>
#include <cstdlib>

bool isPrime(int value) {
  if (value >= 4) {
    int count = 2;
    while (count < value) {
      int residual = value % count;
      if (residual == 0) {
        return false;
      }
      ++count;
    }
  }
  return true;
}

int main(int argc, char** argv) {

  while (true) {
    int random = rand();
    if (isPrime(random)) {
      printf("Prime number: %i\n", random);
      break;
    }
  }

  return 0;
}

