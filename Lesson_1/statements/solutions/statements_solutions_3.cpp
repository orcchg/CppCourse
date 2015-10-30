#include <cstdio>
#include <cstring>
#include "logger.h"

#define VOID -1
#define SIZE 10  // stack size
#define MAXLEN 50  // max length of expression

// Quiz: test the ratio between SIZE and MAXLEN allowing to avoid Segmentation Fault.

/* Brackets */
// ----------------------------------------------------------------------------
/* ( )
 *
 * b10 = ( = 1
 * b11 = ) = 5
 */

enum class Bracket : int {
  NONE = 0,
  B10 = 1, B11 = 5
};

bool isOpenBracket(Bracket bracket) {
  return bracket == Bracket::B10;
}

bool isCloseBracket(Bracket bracket) {
  return bracket == Bracket::B11;
}

Bracket getOpenBracket(Bracket close_bracket) {
  switch (close_bracket) {
    case Bracket::B11: return Bracket::B10;
    default: return Bracket::NONE;
  }
}

Bracket parseChar(char ch) {
  switch (ch) {
    case '(': return Bracket::B10;  case ')': return Bracket::B11;
    default: return Bracket::NONE;
  }
}

/* Stack */
// ----------------------------------------------------------------------------
struct StackItem {
  int number;
  Bracket data;
};

void clear(StackItem stack[]) {
  for (int i = 0; i < SIZE; ++i) {
    stack[i].number = VOID;
    stack[i].data = Bracket::NONE;
  }
}

bool empty(StackItem stack[]) {
  return (stack[0].number == VOID);
}

bool full(StackItem stack[]) {
  return (stack[SIZE - 1].number != VOID);
}

void push(StackItem stack[], Bracket bracket) {
  StackItem aux_stack[SIZE];
  int index = 0;

  if (!full(stack)) {
    for (int i = 0; i < SIZE; ++i) {
      aux_stack[i].data = stack[i].data;
      if (stack[i].number != VOID) {
        ++index;
      }
    }
    aux_stack[index].data = bracket;
    stack[index].number = index;

    for (int i = 0; i < SIZE; ++i) {
      stack[i].data = aux_stack[i].data;
    }
  }
}

Bracket pop(StackItem stack[]) {
  int index = 0;
  Bracket top = Bracket::NONE;

  if (!empty(stack)) {
    for (int i = 0; i < SIZE; ++i) {
      if (stack[i].number != VOID) {
        ++index;
      }
    }
    top = stack[index - 1].data;
    stack[--index].data = Bracket::NONE;
    stack[index].number = VOID;
    return top;
  }
  return Bracket::NONE;
}

/* Solution */
// ----------------------------------------------------------------------------
bool parse(const char* expression) {
  int result = 0;
  int length = strlen(expression);
  Bracket top = Bracket::NONE;

  StackItem stack[SIZE];
  clear(stack);

  for (int i = 0; i < length; ++i) {
    Bracket bracket = parseChar(expression[i]);
    if (isOpenBracket(bracket)) {
      push(stack, bracket);
    } else if (isCloseBracket(parseChar(expression[i]))) {
      top = pop(stack);
      if (top != getOpenBracket(bracket)) {
        result = i;
      }
    }
  }

  if (result == 0 && !empty(stack)) {
    result = 1;
  }
  return result == 0;
}

/* Interface */
// ----------------------------------------------------------------------------
void input() {
  printf("\e[5;00;32mВведите скобочное выражение: \e[m");
  char expression[MAXLEN + 1];
  char ch;
  int index = 0;
  while (index < MAXLEN &&(ch = getchar()) != '\n') {
    expression[index++] = ch;
  }
  expression[index] = 0;

  bool result = parse(expression);
  if (result) {
    INF("Скобочное выражение %s корректно", expression);
  } else {
    ERR("Скобочное выражение %s некорректно!", expression);
  }
}  // O(n)

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 1]: Statements: Solutions 4");
  input();
  DBG("[Lesson 1]: Statements: Solutions 4 [END]");
  return 0;
}

