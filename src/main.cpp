#include <bits/stdc++.h>
#include <experimental/filesystem>
#include "cxxopts.hpp"
#include "logger.hpp"
#include "bprinter/table_printer.h"
#include <thread>

#include "presentation.h"
#include "helper.h"
#include "configer.h"

#include "Solution.h"
#include "SolutionResult.h"
#include "TestResult.h"
#include "CompileResult.h"
#include "RunResult.h"
#include "Verdict.h"
#include "DiffChecker.h"
#include "Checker.h"
#include "Test.h"

#include "definitions.h"

extern configer::configer bconf;

cxxopts::Options get_options(int nargs, char* argv[]) {
	cxxopts::Options opt(argv[0]);

	opt.add_options()
		("t,time", "time limit in seconds", cxxopts::value<double>()->default_value("1.0"))
		("d,diff", "show diff", cxxopts::value<bool>()->default_value("false"))
		("c,cerr", "show compilation errors", cxxopts::value<bool>()->default_value("false"))
		("r,rerr", "show runtime error", cxxopts::value<bool>()->default_value("false"))
// 		("i,inc", "judge on specified tests only", cxxopts::value<std::vector<std::string>>()->default_value("[\\s\\S]*"))
		("s,sol", "solutions to be judged", cxxopts::value<std::vector<std::string>>()->default_value("[\\s\\S]*"))
		("p,pwd", "working path - the directory contains the solutions", cxxopts::value<std::string>()->default_value(DEFAULT_PWD))
		("T,test_path", "test path - the directory contains the tests", cxxopts::value<std::string>()->default_value(DEFAULT_TEST_PATH))
		("I,inp_ext", "input extension", cxxopts::value<std::string>()->default_value(DEFAULT_INPUT_EXTENSION))
		("A,ans_ext", "answer extension", cxxopts::value<std::string>()->default_value(DEFAULT_ANSWER_EXTENSION))
        ("C,checker", "judge with checker", cxxopts::value<std::string>()->default_value(""))
        ("O,opt", "checker options", cxxopts::value<std::string>()->default_value(""))
		("h,help", "show help");

	opt.parse_positional("s");

	return opt;
}

void read_configs(const cxxopts::ParseResult& args) {
	try {
		bconf.set("time_limit", args["t"].as<double>());
		bconf.set("show_compile_errors", args["c"].as<bool>());
		bconf.set("show_diff", args["d"].as<bool>());
		bconf.set("show_error", args["r"].as<bool>());
// 		bconf.set("tests", args["i"].as<std::vector<std::string>>());
		bconf.set("solutions", args["s"].as<std::vector<std::string>>());
		bconf.set("pwd", args["p"].as<std::string>());
		bconf.set("test_path", args["T"].as<std::string>());
		bconf.set("inp_ext", args["I"].as<std::string>());
		bconf.set("ans_ext", args["A"].as<std::string>());
        bconf.set("checker", args["C"].as<std::string>());
        bconf.set("checker_options", args["O"].as<std::string>());
	}
	catch (const std::exception& ex) {
		loge(ex.what());
	}
}

void compile_and_judge(std::map<std::string, SolutionResult>& sol_results, const std::vector<Test>& tests, const Checker& checker) {
	try {
		helper::make_dirs();

        if (checker.raw != "") {
            std::cout << "Using non-default checker: " + presentation::color_string(checker.raw + "." + checker.ext, presentation::Color::Green) << ": ";
            CompileResult checker_compile_result = checker.compile();
            if (checker_compile_result.compile_succeed()) {
                std::cout << presentation::color_string("Compilation succeed", presentation::Color::Green) << "\n";
            }
            else {
                std::cout << presentation::color_string("Compilation failed", presentation::Color::Red);
                std::terminate();
            }
        }

		std::vector<std::thread> threads;

		auto sol_names = bconf.get<std::vector<std::string>>("solutions");

        std::mutex sol_lock;
		for (const std::string& sol_name: sol_names) {
			threads.emplace_back([&] () {
                Solution sol(sol_name, bconf.get<double>("time_limit"));
                SolutionResult sol_result;
                sol_result.compile_result = sol.compile();
                if (sol_result.compile_result.compile_succeed()) {
                    sol_result.judge_result = checker.judge(sol, tests);
                }
                sol_lock.lock();
                sol_results[sol_name] = sol_result;
                sol_lock.unlock();
            });
		}

		for (auto& t: threads) {
			t.join();
		}

		helper::clean();
	}
	catch (const std::exception& ex) {
		loge(ex.what());
	}
}

void print_compile_results(const std::map<std::string, SolutionResult>& sol_results, const Checker& checker) {
	try {
		for (const auto& [sol_name, sol_result]: sol_results) {
			if (sol_result.compile_result.compile_succeed()) {
				std::cout << sol_name << ": "
					<< presentation::color_string("Compilation succeed",
							presentation::Color::Green) << "\n";
			}
			else {
				std::cout << sol_name << ": "
					<< presentation::color_string("Compilation failed", presentation::Color::Red) << "\n";
				if (bconf.get<bool>("show_compile_errors")) {
					std::cout << sol_result.compile_result.compile_errors;
				}
			}
		}
	}
	catch (const std::exception& ex) {
		loge(ex.what());
	}
}

void print_judge_results(const std::map<std::string, SolutionResult>& sol_results, const std::vector<Test>& tests) {
	bprinter::TablePrinter tp(&std::cout);

	tp.AddColumn(presentation::color_string("Test\\Solution",
				presentation::Color::Yellow), 25, true);

	for (auto [sol_name, sol_result]: sol_results) {
		if (sol_result.compile_result.compile_succeed()) {
			std::string colored_sol_name = presentation::color_string("     " + sol_name,
					presentation::Color::Yellow);
			tp.AddColumn(colored_sol_name, colored_sol_name.length() + 1, true);
		}
	}

	tp.PrintHeader();

	for (const auto& test: tests) {
		tp << presentation::color_string(test.name);
		for (const auto& [sol_name, sol_result]: sol_results) {
			if (sol_result.compile_result.compile_succeed()) {
				tp << sol_result.judge_result[test.name].result_string();
			}
		}
	}

	tp.PrintHorizontalLine();

	for (const Verdict& verdict: {Verdict::AC, Verdict::WA, Verdict::TLE, Verdict::RE}) {
		tp << TestResult{verdict, .0, ""}.result_string(false);
		for (const auto& [sol_name, sol_result]: sol_results) {
			if (sol_result.compile_result.compile_succeed()) {
				tp << presentation::color_string(
						helper::format("%d/%d",
							sol_result.judge_result.countByVerdict(verdict),
							(int)tests.size()));
			}
		}
	}

	tp.PrintFooter();
}

void print_errors(const std::map<std::string, SolutionResult>& sol_results) {
	for (const auto& [sol_name, sol_result]: sol_results) {
		std::map<std::string, TestResult> wa_tests = sol_result.judge_result.getTestsByVerdict(Verdict::WA);
		std::map<std::string, TestResult> re_tests = sol_result.judge_result.getTestsByVerdict(Verdict::RE);

		if (bconf.get<bool>("show_diff")) {
			for (const auto& [test_name, test_result]: wa_tests) {
				std::cout << ">> " << sol_name
						<< ", test "
						<< test_name
						<< ", verdict: "
						<< presentation::color_string("Wrong Answer", presentation::Color::Red)
						<< ":\n" << test_result.message << std::endl;
			}
		}

		if (bconf.get<bool>("show_error")) {
			for (const auto& [test_name, test_result]: re_tests) {
				std::cout << ">> " << sol_name
						<< ", test "
						<< test_name
						<< ", verdict: "
						<< presentation::color_string("Runtime Error", presentation::Color::Red)
						<< ":\n" << test_result.message << std::endl;
			}
		}
	}
}

int main(int nargs, char* argv[]) {
	cxxopts::Options opt = get_options(nargs, argv);
	cxxopts::ParseResult args = opt.parse(nargs, argv);

	if (args.count("help")) {
		return std::cout << opt.help({""}) << std::endl, 0;
	}

	read_configs(args);

    auto tests = helper::get_tests(bconf.get<std::string>("test_path"),
            bconf.get<std::string>("inp_ext"),
            bconf.get<std::string>("ans_ext"));

	std::sort(tests.begin(), tests.end(),
			[] (const Test& a, const Test& b) {
				return a.name.length() != b.name.length()
					? a.name.length() < b.name.length()
					: a.name < b.name;
			});

	std::map<std::string, SolutionResult> sol_results;
    Checker* checker = bconf.get<std::string>("checker") == "" ?
                      new DiffChecker()
                      : new Checker(bconf.get<std::string>("checker"),
                              bconf.get<double>("time_limit"),
                              bconf.get<std::string>("checker_options"));

	compile_and_judge(sol_results, tests, *checker);
	print_compile_results(sol_results, *checker);
	print_judge_results(sol_results, tests);
	print_errors(sol_results);
}
