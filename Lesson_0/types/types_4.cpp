#include <climits>
#include <cstdio>

/// @see http://www.cplusplus.com/reference/climits/

int main(int argc, char** argv) {
  
  short int left = 20000;
  short int right = 25000;
  short int sum = left + right;

  int mil = 1000000;
  int bil = 1000000000;
  int mul = mil * bil;

  printf("sum: %hi\n", sum);
  printf("mul: %i\n", mul);

  return 0;
}

