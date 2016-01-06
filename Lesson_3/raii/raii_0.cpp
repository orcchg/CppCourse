#include <fstream>
#include <string>
#include <cstdio>
#include "logger.h"

class File {
public:
  File(const std::string& name);
  ~File();
  
  void read();

private:
  std::string m_url;
  std::fstream m_fs;
};

File::File(const std::string& name)
  : m_url(name), m_fs(name) {
}

File::~File() {
  m_fs.close();
}

void File::read() {
  std::string line;
  while (std::getline(m_fs, line)) {
    printf("%s\n", line.c_str());
  }
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 3]: RAII 0");
  
  {
    INF("Enter block");
    File file("lorem.txt");
    file.read();
	INF("Exit block");
  }

  DBG("[Lesson 3]: RAII 0 [END]");
  return 0;
}
