#include <cstdio>

int main(int argc, char** argv) {

  int array[] = {5, 1, 7, -3, 4, 2, 8, 0, 1, -2, 3, 5, 7, 9, -2, 6};
  int length = sizeof(array) / sizeof(array[0]);

  int sum = 0;
  for (int i = 0; i < length; ++i) {
    sum += array[i];  // sum = sum + a;
  }

  double average = static_cast<double>(sum) / length;

  printf("Average: %lf\n", average);

  return 0;
}

