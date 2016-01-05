#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include "logger.h"

#define SIZE 512

/**
 * Inheritance: polymorphism
 */
class Reader {
public:
  virtual ~Reader();

  virtual void openConnection(const std::string& url) = 0;
  void readData();
  void printData();
  virtual void closeConnection() = 0;

protected:
  char* m_data;

  virtual void processData() = 0;
};

Reader::~Reader() {
  delete [] m_data;
  m_data = nullptr;
}

void Reader::readData() {
  INF("Read data");
  m_data = new char[SIZE + 1];
  memset(m_data, '-', SIZE + 1);
  processData();
}

void Reader::printData() {
  INF("Data: %s", m_data);
}

// ----------------------------------------------
class FileReader : public Reader {
public:
  void openConnection(const std::string& url);
  void closeConnection();

private:
  std::fstream m_fs;

  void processData() override;
};

void FileReader::openConnection(const std::string& url) {
  DBG("File is opened");
  m_fs.open(url, std::fstream::in);
}

void FileReader::closeConnection() {
  DBG("File has been closed");
  m_fs.close();
}

void FileReader::processData() {
  DBG("File: processing data...");
  int offset = 0;
  char ch;
  while (offset < SIZE && m_fs.get(ch)) {
    m_data[offset++] = ch;
  }
  m_data[offset] = '\0';
}

// ----------------------------------------------
class DatabaseReader : public Reader {
public:
  void openConnection(const std::string& url);
  void closeConnection();

private:
  void processData() override;
};

void DatabaseReader::openConnection(const std::string& url) {
  WRN("Database has connected");
}

void DatabaseReader::closeConnection() {
  WRN("Database has disconnected");
}

void DatabaseReader::processData() {
  WRN("Database: processing data...");
  for (size_t i = 0; i <= SIZE; ++i) {
    m_data[i] = 'a' + rand() % 26;
  }
}

// ----------------------------------------------
class NetworkReader : public Reader {
public:
  void openConnection(const std::string& url);
  void closeConnection();

private:
  void processData() override;
};

void NetworkReader::openConnection(const std::string& url) {
  ERR("Network connection established");
}

void NetworkReader::closeConnection() {
  ERR("Network connection lost");
}

void NetworkReader::processData() {
  ERR("Network: receiving data...");
  memset(m_data, '*', SIZE + 1);
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Abstract 1");

  std::vector<Reader*> readers = {new FileReader(), new DatabaseReader(), new NetworkReader()};

  for (auto ptr : readers) {
    ptr->openConnection(argv[1]);
    ptr->readData();
    ptr->printData();
    ptr->closeConnection();
    std::cout << std::endl;
    delete ptr;
  }

  DBG("[Lesson 5]: Abstract 1 [END]");
  return 0;
}

