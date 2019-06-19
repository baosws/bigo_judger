#include "JudgeResult.h"

TestResult& JudgeResult::operator[](const std::string& test_name) {
    return test_results[test_name];
}

TestResult& JudgeResult::operator[](const std::string& test_name) const {
    return test_results[test_name];
}

int JudgeResult::countByVerdict(const Verdict& verdict) const {
    return std::count_if(test_results.begin(), test_results.end(), [&] (const std::pair<std::string, TestResult>& it) {
            return it.second.verdict == verdict;
            });
}

JudgeResult::Container JudgeResult::getTestsByVerdict(const Verdict& verdict) const {
    Container wa_tests;
    std::copy_if(test_results.begin(),
            test_results.end(),
            std::inserter(wa_tests, wa_tests.end()),
            [&] (const std::pair<std::string, TestResult>& it) {
            return it.second.verdict == verdict;
            });
    return wa_tests;
}
