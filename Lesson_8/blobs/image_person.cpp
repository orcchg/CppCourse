#include "image_person.h"

ImagePerson::ImagePerson(
    const std::string& name,
    const std::string& last_name,
    int age,
    const std::string& gender,
    int height,
    double weight)
  : Person(name, last_name, age, gender, height, weight) {
}

void ImagePerson::setImage(uint8_t* image) {
  this->image = image;
}

