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

ImagePerson::~ImagePerson() {
  delete [] image;  image = nullptr;
}

void ImagePerson::setImage(uint8_t* raw, int size, int w, int h) {
  image = new uint8_t[size];  // deep copy
  for (int i = 0; i < size; ++i) {
    image[i] = raw[i];
  }
  image_size = size;
  image_width = w;
  image_height = h;
}

