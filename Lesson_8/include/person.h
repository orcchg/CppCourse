#ifndef PERSON__H__
#define PERSON__H__

#include <string>

struct Person {
  std::string name;
  std::string last_name;
  int age;
  std::string gender;
  int height;
  double weight;

  Person(
    const std::string& name,
    const std::string& last_name,
    int age,
    const std::string& gender,
    int height,
    double weight);

  virtual ~Person();
};

#endif  // PERSON__H__

