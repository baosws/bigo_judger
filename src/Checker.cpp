#include "Checker.h"
#include "helper.h"
#include "configer.h"

extern configer::configer bconf;
Checker::Checker() {}

Checker::Checker(const std::string& filename, double timeout, const std::string& options): Solution(filename, timeout) {
    run_command = JUDGE_BIN "/\"" + raw + "\"" + " \"%s\" \"%s\" \"%s\" " + options + " < \"%s\"";
}

const int EXIT_AC = 42;
const int EXIT_WA = 43;

CompileResult Checker::compile() const {
    return Solution::compile();
}

std::string Checker::check(const std::string& in, const std::string& out, const std::string& ans) const {
    helper::make_dir(JUDGE_FEEDBACK);
    std::string run_command = helper::format(this->run_command, in.data(), ans.data(), JUDGE_FEEDBACK.data(), out.data());

    int exit_code = pclose(popen(run_command.data(), "r")) >> 8;
    if (exit_code == EXIT_AC) {
        return "";
    }
    return "Diffpos:\n" + helper::read_file(JUDGE_DIFFPOS) + "Message:\n" + helper::read_file(JUDGE_MESSAGE);
}

TestResult Checker::judge(const Solution& sol, const Test& test) const {
    RunResult run_result = sol.run(test.in(), JUDGE_OUTPUT);

    if (run_result.timeout && run_result.error == "") {
        return {Verdict::TLE, run_result.time, ""};
    }
    else if (run_result.error != "") {
        return {Verdict::RE, run_result.time, run_result.error};
    }
    else {
        std::string diff_out_ans = this->check(test.in(), JUDGE_OUTPUT, test.ans());
        if (diff_out_ans == "") {
            return {Verdict::AC, run_result.time, ""};
        }
        else {
            return {Verdict::WA, run_result.time, diff_out_ans};
        }
    }
}

JudgeResult Checker::judge(const Solution& sol, const std::vector<Test>& tests) const {
    JudgeResult sol_result;
    for (auto& test: tests) {
        sol_result[test.name] = this->judge(sol, test);
    }

    return sol_result;
}
