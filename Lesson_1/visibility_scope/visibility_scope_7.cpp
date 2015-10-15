#include <cstdio>

int global_variable = 1;

int main(int argc, char** argv) {  // main block
  printf("[Lesson 1]: Visibility scope 7\n");

  int local_variable = 2;
  bool boolean_expression = true;
  
  {  // block 1
    int local_variable = 3;
    printf("[Block    1]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);
    
    int index = 0;

    if (boolean_expression) {  // block 2
      {  // block 3
        int local_variable = 4;
        printf("[Block    3]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);

        while (index < 2) {  // block 4
          printf("[Block    4]: Global variable = %i, Local variable = %i, Index = %i\n", global_variable, local_variable, index);
          ++index;
        }  // end block 4

      }  // end block 3
      printf("[Block    2]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);
    }  // block 2

  }  // end block 1

  printf("[Main Block]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);

  printf("[Lesson 1]: Visibility scope 7 [END]\n\n");
  return 0;
}  // end main block

