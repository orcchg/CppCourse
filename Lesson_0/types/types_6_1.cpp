#include <cstdio>

int main(int argc, char** argv) {
  
  int a = 0;
  a = ++a + a++;

  printf("a = %i\n", a);

  return 0;
}

