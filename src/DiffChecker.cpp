#include "DiffChecker.h"
#include "helper.h"

DiffChecker::DiffChecker() {}

std::string DiffChecker::check(const std::string& in, const std::string& out, const std::string& ans) const {
    return helper::diff(out, ans);
}

CompileResult DiffChecker::compile() const {
    return {""};
}
