#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv) {

  int random = rand();
  bool flag = static_cast<bool>(random % 2);

  if (flag) {
    printf("flag is true, value is %i\n", random);
  } else {
    printf("flag is false, value is %i\n", random);
  }

  return 0;
}

