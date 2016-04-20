#include <cstdio>

int main(int argc, char** argv) {
  
  int a = 0;

  a = 5, 9;
  printf("a = %i\n", a);

  a = 5, 9, 3;
  printf("a = %i\n", a);

  a = (5, 9), 3;
  printf("a = %i\n", a);

  a = 5, (9, 3);
  printf("a = %i\n", a);

  a = (5, 9), (3, 7);
  printf("a = %i\n", a);

  return 0;
}

