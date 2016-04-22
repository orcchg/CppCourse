#include <cstdio>

int main(int argc, char** argv) {
  
  int a = 0;
  a++;  // postfix increment
  int b = a;

  printf("a = %i, b = %i\n", a, b);


  ++a;  // a = a + 1;
  --a;  // a = a - 1;

  a++;  // a = a + 1;
  a--;  // a = a - 1;

  return 0;
}

