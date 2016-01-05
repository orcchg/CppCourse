#include <algorithm>
#include <vector>
#include "logger.h"

/**
 * Inheritance: derived ~dtor
 */
class Unit {
protected:
  Unit(int health, int armor, int damage, int speed);

public:
  ~Unit();

  virtual void attack() const = 0;

private:
  int m_health;
  int m_armor;
  int m_damage;
  int m_speed;
};

Unit::Unit(int health, int armor, int damage, int speed)
  : m_health(health), m_armor(armor), m_damage(damage), m_speed(speed) {
  DBG("Unit ctor(%i, %i, %i, %i)", m_health, m_armor, m_damage, m_speed);
}

Unit::~Unit() {
  DBG("Unit ~dtor()");
}

void Unit::attack() const {
  DBG("Unit attacks");
}

// ----------------------------------------------
class Footman : public Unit {
public:
  Footman();
  ~Footman();

  void attack() const override;
};

Footman::Footman() : Unit(420, 7, 21, 270) {
  INF("Footman ctor()");
}

Footman::~Footman() {
  INF("Footman ~dtor()");
}

void Footman::attack() const {
  INF("Footman attacks");
}

// ----------------------------------------------
class Archer : public Unit {
public:
  Archer();
  ~Archer();

  void attack() const override;
};

Archer::Archer() : Unit(235, 4, 17, 280) {
  WRN("Archer ctor()");
}

Archer::~Archer() {
  WRN("Archer ~dtor()");
}

void Archer::attack() const {
  WRN("Archer attacks");
}

// ----------------------------------------------
class Knight : public Unit {
public:
  Knight();
  ~Knight();

  void attack() const override;
};

Knight::Knight() : Unit(875, 11, 36, 340) {
  ERR("Knight ctor()");
}

Knight::~Knight() {
  ERR("Knight ~dtor()");
}

void Knight::attack() const {
  ERR("Knight attacks");
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Polymorphism 2");

  Footman footman;
  Archer archer;
  Knight knight;

  DBG("[Lesson 5]: Polymorphism 2 [END]");
  return 0;
}

