#include <string>
#include <vector>
#include "logger.h"

struct Person {
  int id;
  std::string name;
  std::string email;

  Person(int id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {
  }
};

class IStorage {
public:
  virtual ~IStorage() {}

  virtual void init() = 0;
  virtual void release() = 0;

  virtual Person getPerson(int id) = 0;
  virtual int addPerson(const Person& person) = 0;
  virtual void removePerson(int id) = 0;
  virtual size_t size() = 0;
};

// ----------------------------------------------
class Database : public IStorage {
public:
  Database() {}
  ~Database() {}

  void init() override {}
  void release() override {}

  Person getPerson(int id) override {}
  int addPerson(const Person& person) override {}
  void removePerson(int id) override {}
  size_t size() override {}

private:
  /* local impl */
};

// ----------------------------------------------
class Network : public IStorage {
public:
  Network() {}
  ~Network() {}

  void init() override {}
  void release() override {}

  Person getPerson(int id) override {}
  int addPerson(const Person& person) override {}
  void removePerson(int id) override {}
  size_t size() override {}

private:
  /* network impl */
};

// ----------------------------------------------
template <typename Iter>
void addAll(Iter begin, Iter end, IStorage* storage) {
  while (begin != end) {
    storage->addPerson(*begin++);
  }
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Abstract 4");

  std::vector<Person> array;
  array.emplace_back(0, "Torin", "torin@hobbit.com");
  array.emplace_back(1, "Frodo", "frodo@lotr.com");
  array.emplace_back(2, "Galdalf", "the_grey@lotr.com");
  array.emplace_back(3, "Sauron", "evil@lotr.com");

  Database database;
  addAll(array.begin(), array.end(), &database);

  Network remote;
  addAll(array.begin(), array.end(), &remote);

  DBG("[Lesson 5]: Abstract 4 END");
  return 0;
}

