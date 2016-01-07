#ifndef SYMBOL_TABLE__H__
#define SYMBOL_TABLE__H__

#include <string>
#include "function_ptr_table.h"

class SymbolTable {
public:
  SymbolTable();
  ~SymbolTable();

  bool loadLibrary(const std::string& filename);

private:
  FunctionPtrTable* m_symbol_table;
  void* m_handle;

  bool loadSymbols();
  bool checkError();
};

#endif  // SYMBOL_TABLE__H__

