#include <cstdio>

typedef void (*BAR_V) ();
typedef void (*BAR_I) (int);

void bar() {
  printf("VOID\n");
}

void bar(int x) {
  printf("INT\n");
}

int main(int argc, char** argv) {
    BAR_V vp = (BAR_V) 0x400526;
    BAR_I ip = (BAR_I) 0x400537;

    vp();
    ip(5);
}

