#ifndef CHECKER
#define CHECKER
#include <bits/stdc++.h>
#include "Solution.h"
#include "definitions.h"
#include "TestResult.h"
#include "JudgeResult.h"
#include "Test.h"

struct Checker: Solution {
    Checker();
    Checker(const std::string& filename, double timeout, const std::string& options = "");
    virtual CompileResult compile() const;
    virtual std::string check(const std::string& in, const std::string& out, const std::string& ans) const;

    TestResult judge(const Solution& sol, const Test& test) const;
    JudgeResult judge(const Solution& sol, const std::vector<Test>& tests) const;
};

#endif
