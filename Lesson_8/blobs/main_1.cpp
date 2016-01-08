#include <vector>
#include <cstdlib>
#include "database_v2.h"
#include "image.h"
#include "image_person.h"
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

  PNGImage image_0("blobs/images/pr_butterfly.png");
  PNGImage image_1("blobs/images/pr_clock.png");
  PNGImage image_2("blobs/images/pr_dice.png");
  PNGImage image_3("blobs/images/pr_extend.png");
  PNGImage image_4("blobs/images/pr_newyear.png");
  PNGImage image_5("blobs/images/pr_protect.png");
  PNGImage image_6("blobs/images/pr_star.png");

  image_1.rawImage("raw_png.txt");

  persons->at(0).setImage(image_0.getImage(), image_0.getSize(), image_0.getWidth(), image_0.getHeight());
  persons->at(1).setImage(image_1.getImage(), image_1.getSize(), image_1.getWidth(), image_1.getHeight());
  persons->at(2).setImage(image_2.getImage(), image_2.getSize(), image_2.getWidth(), image_2.getHeight());
  persons->at(3).setImage(image_3.getImage(), image_3.getSize(), image_3.getWidth(), image_3.getHeight());
  persons->at(4).setImage(image_4.getImage(), image_4.getSize(), image_4.getWidth(), image_4.getHeight());
  persons->at(5).setImage(image_5.getImage(), image_5.getSize(), image_5.getWidth(), image_5.getHeight());
  persons->at(6).setImage(image_6.getImage(), image_6.getSize(), image_6.getWidth(), image_6.getHeight());
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

  INF("ImagePerson: name=\'%s\', lastName=\'%s\', age=\'%i\', gender=\'%s\', height=\'%i\', weight=\'%lf\', image=\'%p\'",
      person.name.c_str(), person.last_name.c_str(), person.age, person.gender.c_str(), person.height, person.weight, person.image);

  // TODO: task 4: Uncomment and check how Database has changed
  // deletePerson(id, &database);

  savePNGImage("sample_image.png", person.image, person.image_width, person.image_height, person.image_size);
  WRN("Raw image");
  rawImageWrite("raw_db.txt", person.image, person.image_size);

  for (auto& person : persons) {
    delete [] person.image;  person.image = nullptr;
  }

  DBG("[Lesson 8]: Database 1 [END]");
  return 0;
}

