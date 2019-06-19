#ifndef DIFF_CHECKER
#define DIFF_CHECKER
#include "Checker.h"
#include "definitions.h"

struct DiffChecker: Checker {
    DiffChecker();
    CompileResult compile() const;
    std::string check(const std::string& in, const std::string& out, const std::string& ans) const;
};
#endif
