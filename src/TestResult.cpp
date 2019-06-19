#include "TestResult.h"
#include "presentation.h"
#include "helper.h"
#include <logger.hpp>
std::string TestResult::result_string(bool include_time) const {
    static std::map<Verdict, std::string> color_string_by_code = {
        {Verdict::AC, color_string("AC", presentation::Color::Green)},
        {Verdict::WA, color_string("WA",presentation::Color::Red)},
        {Verdict::TLE, color_string("TLE", presentation::Color::Orange)},
        {Verdict::RE, color_string("RE", presentation::Color::Red)}
    };

    return color_string_by_code[verdict] + (include_time ? helper::format("(%dms)", int(time * 1000)) : "");
}
