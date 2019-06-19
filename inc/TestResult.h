#ifndef TEST_RESULT
#define TEST_RESULT
#include "Verdict.h"
#include <bits/stdc++.h>
struct TestResult {
    Verdict verdict = Verdict::NA;
    double time;
    std::string message;

    std::string result_string(bool include_time = true) const;
};
#endif
