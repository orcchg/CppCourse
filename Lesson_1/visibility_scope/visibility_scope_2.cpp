#include <cstdio>

int global_variable = 1;

int main(int argc, char** argv) {  // main block
  printf("[Lesson 1]: Visibility scope 2\n");

  bool boolean_expression = true;
  int local_variable = 2;
  
  if (boolean_expression) {  // block 1
    int local_variable = 3;
    printf("[Block    1]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);
  }  // end block 1

  printf("[Main Block]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);

  printf("[Lesson 1]: Visibility scope 2 [END]\n\n");
  return 0;
}  // end main block

