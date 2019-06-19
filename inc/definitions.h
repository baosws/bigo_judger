#ifndef DEFINES
#define DEFINES

// judge's directories

#define JUDGE_FEEDBACK       ("./judge/" + std::to_string(std::this_thread::get_id()))
#define JUDGE_DIFFPOS        (JUDGE_FEEDBACK + "/diffposition.txt")
#define JUDGE_MESSAGE        (JUDGE_FEEDBACK + "/judgemessage.txt")
#define JUDGE_DIFF_OUT_ANS   ("./judge/diff_out_ans_" + std::to_string(std::this_thread::get_id()))
#define JUDGE_DIR            "./judge/"
#define JUDGE_COMPILE_ERRORS ("./judge/compile_errors_" + std::to_string(std::this_thread::get_id()))
#define JUDGE_OUTPUT         ("./judge/output_" + std::to_string(std::this_thread::get_id()))
#define JUDGE_RUNTIME_ERROR  ("./judge/runtime_error_" + std::to_string(std::this_thread::get_id()))
#define JUDGE_BIN            "./judge/bin/"

// constants
#define BUFF_SIZE 256
#define TIMEOUT_EXIT "timeout: the monitored command dumped core\n"

// team's directories
#define DEFAULT_PWD              "./"
#define DEFAULT_TEST_PATH        "TestData/"
#define DEFAULT_INPUT_EXTENSION  "in"
#define DEFAULT_ANSWER_EXTENSION "ans"

#endif
