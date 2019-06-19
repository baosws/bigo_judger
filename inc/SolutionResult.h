#ifndef SOLUTION_RESULT
#define SOLUTION_RESULT
#include "CompileResult.h"
#include "JudgeResult.h"

struct SolutionResult {
    CompileResult compile_result;
    JudgeResult judge_result;
};
#endif
