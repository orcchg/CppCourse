#include "person.h"

Person::Person(
    const std::string& name,
    const std::string& last_name,
    int age,
    const std::string& gender,
    int height,
    double weight)
  : name(name)
  , last_name(last_name)
  , age(age)
  , gender(gender)
  , height(height)
  , weight(weight) {
}

