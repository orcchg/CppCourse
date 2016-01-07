#ifndef FUNCTION_PTR_TABLE__H__
#define FUNCTION_PTR_TABLE__H__

#include <string>

namespace lib {

typedef void (*fptr_printString) (const std::string& str);

}

typedef void (*fptr_printValue) (int value);

typedef struct {
    lib::fptr_printString printString;
    fptr_printValue printValue;
} FunctionPtrTable;

#endif  // FUNCTION_PTR_TABLE__H__

