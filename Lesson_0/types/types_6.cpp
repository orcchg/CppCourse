#include <cstdio>

int main(int argc, char** argv) {
  
  int a = 0;
  int b = ++a;  // prefix

  a = 0;
  int c = a++;  // postfix

  printf("a = %i, b = %i, c = %i\n", a, b, c);

  return 0;
}


int prefix(int a) {
  a = a + 1;
  return a;
}

int postfix(int a) {
  int b = a;
  a = a + 1;
  return b;
}

