#include <dlfcn.h>
#include "logger.h"
#include "symbol_table.h"

// @see http://man7.org/linux/man-pages/man3/dlopen.3.html

namespace lib {

void (*printString)(const std::string& str);

}

void (*printValue)(int value);

// ----------------------------------------------------------------------------
SymbolTable::SymbolTable()
  : m_symbol_table(nullptr)
  , m_handle(nullptr) {
}

SymbolTable::~SymbolTable() {
  delete m_symbol_table;  m_symbol_table = nullptr;

  if (m_handle != nullptr) {
    dlclose(m_handle);
  } 
  m_handle = nullptr;
}

bool SymbolTable::loadLibrary(const std::string& filename) {
  if (m_handle == nullptr) {
    m_handle = dlopen(filename.c_str(), RTLD_LAZY | RTLD_LOCAL);
    if (m_handle == nullptr) {
      return false;
    }
    m_symbol_table = new FunctionPtrTable();
    if (!loadSymbols()) {
      return false;
    }
  }
  return true;
}

bool SymbolTable::loadSymbols() {
  bool flag = true;
  m_symbol_table->printString = (lib::fptr_printString) dlsym(m_handle, "_ZN3lib11printStringERKSs");
  lib::printString = m_symbol_table->printString;
  flag &= checkError();
  m_symbol_table->printValue = (fptr_printValue) dlsym(m_handle, "_Z10printValuei");
  printValue = m_symbol_table->printValue;
  flag &= checkError();
  return flag;
}

bool SymbolTable::checkError() {
  const char* error = nullptr;
  if ((error = dlerror()) != nullptr) {
    ERR("Load symbols error: %s", error);
    return false;
  }
  return true;
}

