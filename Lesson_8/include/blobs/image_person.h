#ifndef IMAGE_PERSON__H__
#define IMAGE_PERSON__H__

#include <string>
#include "person.h"

struct ImagePerson : public Person {
  uint8_t* image;  // raw bytes of image
  int image_size;  // in bytes
  int image_width;
  int image_height;

  ImagePerson(
    const std::string& name,
    const std::string& last_name,
    int age,
    const std::string& gender,
    int height,
    double weight);

  virtual ~ImagePerson();

  void setImage(uint8_t* image, int size, int w, int h);
};

#endif  // IMAGE_PERSON__H__

