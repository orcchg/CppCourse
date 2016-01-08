#include <vector>
#include <cstdlib>
#include "database_v2.h"
#include "person.h"
#include "logger.h"

/* Prepare data */
// ----------------------------------------------------------------------------
void generateData(std::vector<ImagePerson>* persons) {
  persons->emplace_back("Vladimir", "Sidorov", 26, "Male", 177, 72.5);  // 0
  persons->emplace_back("Sveta", "Sokolova", 25, "Female", 168, 49.9);  // 1
  persons->emplace_back("Marquiz", "De Sad", 45, "Male", 169, 73.1);    // 2
  persons->emplace_back("Petr", "Osipov", 28, "Male", 174, 68.5);       // 3
  persons->emplace_back("Jack", "Sparrow", 32, "Male", 178, 70.2);      // 4
  persons->emplace_back("Coco", "Shanel", 71, "Female", 165, 60.3);     // 5
  persons->emplace_back("Alexander", "Druz", 58, "Male", 178, 72.4);    // 6
}

/* Work with Database */
// ----------------------------------------------------------------------------
void addPersons(const std::vector<ImagePerson>& persons, DatabaseV2* database) {
  for (auto& person : persons) {
    database->addPerson(person);
  }
}

ImagePerson readRandomPerson(DatabaseV2* database, int& input_id) {
  input_id = rand() % 7;
  return database->readPerson(input_id);
}

void deletePerson(int id, DatabaseV2* database) {
  database->deletePerson(id);
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 8]: Database 1");

  std::vector<ImagePerson> persons;
  generateData(&persons);

  DatabaseV2 database;
  addPersons(persons, &database);

  int id = 0;
  ImagePerson person = readRandomPerson(&database, id);

  INF("ImagePerson: name=\'%s\', lastName=\'%s\', age=\'%i\', gender=\'%s\', height=\'%i\', weight=\'%lf\'",
      person.name.c_str(), person.last_name.c_str(), person.age, person.gender.c_str(), person.height, person.weight);

  // TODO: task 4: Uncomment and check how Database has changed
  // deletePerson(id, &database);

  DBG("[Lesson 8]: Database 1 [END]");
  return 0;
}

