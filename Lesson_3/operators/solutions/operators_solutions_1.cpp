#include <iomanip>
#include <iostream>
#include <cstdio>
#include "Complex.h"

Complex input() {
  double real, image;
  printf("\e[5;00;32mВведите комплексное число: \e[m");
  scanf("%lf %lf", &real, &image);

  Complex complex(real, image);
  return complex;  // return value optimization (RVO)
}

/* Input / Output */
// ----------------------------------------------
std::ostream& operator << (std::ostream& out, const Complex& obj) {
  out << "(" << obj.getReal() << ", " << obj.getImage() << "i)";
  return out;
}

/* Main */
// ----------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 3]: Operators: Solutions 1");

  Complex first = input();
  Complex second = input();

  std::cout << "Сложение: " << first + second << "\n";
  std::cout << "Вычитание: " << first - second << "\n";
  std::cout << "Умножение: " << first * second << "\n";
  std::cout << "Деление: " << first / second << "\n";

  std::cout << "Плюс (1-е): " << +first << "\n";
  std::cout << "Минус (1-е): " << -first << "\n";

  std::cout << "Равенство: " << std::boolalpha << (first == second) << "\n";
  std::cout << "Неравенство: " << std::boolalpha << (first != second) << std::noboolalpha << "\n";

  std::cout << "Инкеремет: " << ++first << "\n";
  std::cout << "Декремент: " << --first << "\n";
  std::cout << "Постфиксный инкремент (1-е): " << first++ << "\n";
  std::cout << "Постфиксный декремент (1-е): " << first-- << "\n";

  DBG("[Lesson 3]: Operators: Solutions 1 [END]");
  return 0;
}

