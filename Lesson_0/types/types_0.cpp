#include <cstdio>

int main(int argc, char** argv) {

  int left = 16;
  int right = 5;

  int sum = left + right;  // 1
  int dif = left - right;  // 2
  int mul = left * right;  // 3
  int div = left / right;  // 4
  int res = left % right;  // 5

  printf("sum: %i\n", sum);
  printf("dif: %i\n", dif);
  printf("mul: %i\n", mul);
  printf("div: %i\n", div);
  printf("res: %i\n", res);

  return 0;
}

