#include <iostream>
#include <map>
#include <string>
#include <utility>
#include "logger.h"

/**
 * Inheritance: interfaces
 */
 enum Gender { MALE, FEMALE };
 
class IProfile {
public:
  virtual ~IProfile() {}

  virtual int getId() const = 0;
  virtual std::string getName() const = 0;
  virtual size_t getAge() const = 0;
  virtual Gender getGender() const = 0;
  
  virtual void subsribe(int token) = 0;
  virtual void adjustSettings() = 0;
};

// ----------------------------------------------
class MambaProfile : public IProfile {
public:
  int getId() const override final;
  std::string getName() const override final;
  size_t getAge() const override final;
  Gender getGender() const override final;
  
  void subsribe(int token) override;
  void adjustSettings() override;
};

// ----------------------------------------------
class BadooProfile : public IProfile {
public:
  int getId() const override final;
  std::string getName() const override final;
  size_t getAge() const override final;
  Gender getGender() const override final;
  
  void subsribe(int token) override;
  void adjustSettings() override;
};

// ----------------------------------------------
enum ProfileType { MAMBA = 0, BADOO = 1 };

namespace Factory {

IProfile* create(ProfileType type) {
  switch (type) {
    case ProfileType::MAMBA: return new MambaProfile();
	case ProfileType::BADOO: return new BadooProfile();
    default: return nullptr;
  }
}

}

void addToMap(std::map<std::string, IProfile*>* table, IProfile* profile) {
  std::pair<std::string, IProfile*> item(profile->getName(), profile);
  table->insert(item);
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Abstract 0.1");

  std::map<std::string, IProfile*> table;
  
  IProfile* mamba = Factory::create(ProfileType::MAMBA);
  IProfile* badoo = Factory::create(ProfileType::BADOO);
  addToMap(&table, mamba);
  addToMap(&table, badoo);
  
  for (auto& item : table) {
    delete item.second;
  }
  table.clear();

  DBG("[Lesson 5]: Abstract 0.1 [END]");
  return 0;
}

