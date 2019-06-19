#ifndef JUDGE_RESULT
#define JUDGE_RESULT
#include "TestResult.h"
#include "definitions.h"

struct JudgeResult {
        typedef std::map<std::string, TestResult> Container;
        mutable Container test_results;
        TestResult& operator[](const std::string& test_name);
        TestResult& operator[](const std::string& test_name) const;
        int countByVerdict(const Verdict& verdict) const;
        Container getTestsByVerdict(const Verdict& verdict) const;
    };
#endif
