#include "CompileResult.h"
bool CompileResult::compile_succeed() const {
    return compile_errors == "";
}
