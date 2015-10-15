#include <cstdio>

int global_variable = 1;

int main(int argc, char** argv) {  // main block
  printf("[Lesson 1]: Visibility scope 1\n");

  int local_variable = 2;
  
  {  // block 1
    int local_variable = 3;
    printf("[Block    1]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);
  }  // end block 1

  printf("[Main Block]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);

  printf("[Lesson 1]: Visibility scope 1 [END]\n\n");
  return 0;
}  // end main block

