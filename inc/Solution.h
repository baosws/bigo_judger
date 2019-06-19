#ifndef SOLUTION
#define SOLUTION
#include "CompileResult.h"
#include "RunResult.h"
#include <bits/stdc++.h>
struct Solution {
    std::string run_command;
    std::string compile_cmd;
    std::string raw;
    std::string ext;
    Solution();
    Solution(const std::string& filename, double time_out = 1);
    virtual CompileResult compile() const;
    RunResult run(const std::string& in, const std::string& out) const;
};
#endif
