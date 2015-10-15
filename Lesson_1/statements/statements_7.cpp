#include <cstdio>
#include "logger.h"

#define ITEMS 6

enum class MenuItem : int {
  CAMPAIGN = 0,
  BATTLE_NET = 1,
  LOAD_GAME = 2,
  SETTINGS = 3,
  CREDITS = 4,
  QUIT = 5
};

void displayMenu() {
  printf("Кампания\n");
  printf("Сетевая игра\n");
  printf("Загрузить игру\n");
  printf("Настройки\n");
  printf("Авторы\n");
  printf("Выход\n");
}

void selectMenuItem(MenuItem item) {
    printf("Выбрано: ");
    switch (item) {
      case MenuItem::CAMPAIGN:
        printf("Кампания\n");
        break;
      case MenuItem::BATTLE_NET:
        printf("Сетевая игра\n");
        break;
      case MenuItem::LOAD_GAME:
        printf("Загрузить игру\n");
        break;
      case MenuItem::SETTINGS:
        printf("Настройки\n");
        break;
      case MenuItem::CREDITS:
        printf("Авторы\n");
        break;
      case MenuItem::QUIT:
        printf("Выход\n");
        break;
      default:
        ERR("Invalid menu item!");
        break;
    }
}

int main(int argc, char** argv) {
  DBG("[Lesson 1]: Statements 7");

  displayMenu();
  printf("\e[5;00;32mВыберите пункт меню: \e[m");
  MenuItem item = MenuItem::QUIT;
  scanf("%i", &item);
  selectMenuItem(item);

  DBG("[Lesson 1]: Statements 7 [END]");
  return 0;
}

