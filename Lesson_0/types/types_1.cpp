#include <cstdio>

int main(int argc, char** argv) {
  
  double left = 16;
  double right = 5;

  double sum = left + right;  // 1
  double dif = left - right;  // 2
  double mul = left * right;  // 3
  double div = left / right;  // 4
  // double res = left % right;  // 5

  printf("sum: %lf\n", sum);
  printf("dif: %lf\n", dif);
  printf("mul: %lf\n", mul);
  printf("div: %lf\n", div);
  // printf("res: %lf\n", res);

  return 0;
}

