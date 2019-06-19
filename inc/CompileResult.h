#ifndef COMPILE_RESULT
#define COMPILE_RESULT
#include <bits/stdc++.h>
#include "definitions.h"

struct CompileResult {
    std::string compile_errors;
    bool compile_succeed() const;
};
#endif
