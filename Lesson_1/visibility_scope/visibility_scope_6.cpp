#include <cstdio>

int global_variable = 1;

int main(int argc, char** argv) {  // main block
  printf("[Lesson 1]: Visibility scope 6\n");

  int local_variable = 2;
  bool boolean_expression = true;
  
  {  // block 1
    int local_variable = 3;
    printf("[Block    1]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);
    
    if (boolean_expression) {  // block 2
      {  // block 3
        int local_variable = 4;
        printf("[Block    3]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);
      }  // end block 3
      printf("[Block    2]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);
    }  // block 2

  }  // end block 1

  printf("[Main Block]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);

  printf("[Lesson 1]: Visibility scope 6 [END]\n\n");
  return 0;
}  // end main block

