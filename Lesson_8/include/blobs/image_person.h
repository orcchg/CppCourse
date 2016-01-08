#ifndef IMAGE_PERSON__H__
#define IMAGE_PERSON__H__

#include <string>
#include "person.h"

struct ImagePerson : public Person {
  uint8_t* image;  // raw bytes of image

  ImagePerson(
    const std::string& name,
    const std::string& last_name,
    int age,
    const std::string& gender,
    int height,
    double weight);

  void setImage(uint8_t* image);
};

#endif  // IMAGE_PERSON__H__

