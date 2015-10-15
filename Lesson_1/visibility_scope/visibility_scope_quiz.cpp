#include <cstdio>

int global_variable = 1;

int main(int argc, char** argv) {
  printf("[Lesson 1]: Visibility scope quiz\n");

  int local_variable = 2;
  bool boolean_expression = true;
  
  {
    int local_variable = 3;
    printf("[Block    ?]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);
    
    int index = 0;

    while (boolean_expression) {
      {
        int local_variable = 4;
        printf("[Block    ?]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);

        do {
          printf("[Block    ?]: Global variable = %i, Local variable = %i, Index = %i\n", global_variable, local_variable, index);
          ++index;
        } while (index < 2);

        if (index == 2) {
          boolean_expression = false;
        }
      }
      printf("[Block    ?]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);
    }

  }

  printf("[Block    ?]: Global variable = %i, Local variable = %i\n", global_variable, local_variable);

  printf("[Lesson 1]: Visibility scope quiz [END]\n\n");
  return 0;
}

