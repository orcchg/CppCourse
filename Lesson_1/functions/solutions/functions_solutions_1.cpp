#include <cmath>
#include <cstdlib>
#include <ctype.h>  // isspace()
#include "logger.h"

namespace home {

bool isnum(char ch) {
  return ch >= '0' && ch <= '9';
}

bool isspace_or_zero(char ch) {
  return isspace(ch) || ch == '0';
}

int atoi(const char* str) {
  if (str == nullptr) {
    return 0;
  }

  while (isspace_or_zero(*str++));  // discard leading whitespaces and zeros
  --str;

  int sign = *str == '-' ? ++str, -1 : 1;
  int power = -1;
  while (isnum(str[++power]));

  int answer = 0;
  while (power > 0) {
    answer += std::pow(10, --power) * (*str++ - '0');
  }

  return answer * sign;
}

}

void unitTest() {
  bool flag = true;

  while (flag) {
    int power = rand() % 9 + 1;
    char* str = new char[power + 1];
    str[0] = rand() % 2 == 0 ? '-' : ' ';
    for (int i = 1; i <= power; ++i) {
      str[i] = rand() % 10 + '0';
    }
    int answer = home::atoi(str);
    int etalon = std::atoi(str);
    if (answer != etalon) {
      ERR("Test failed: expected = %i, actual = %i, string %s", etalon, answer, str);
      flag = false;
    } else {
      INF("OK: %s", str);
    }
    delete [] str;  str = nullptr;
  }
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Functions: Solutions 1");
  unitTest();
  DBG("[Lesson 1]: Functions: Solutions 1 [END]");
  return 0;
}

