#include "helper.h"
#include <experimental/filesystem>
#include <thread>

namespace std {
	std::string to_string(const std::thread::id& id) {
		std::stringstream s;
		s << id;
		return s.str();
	}
}

namespace helper {
	std::string extension(const std::string& name) {
        if (name.find('.') == std::string::npos) {
            return "";
        }
		return name.substr(name.find_last_of(".") + 1);
	}

	std::string raw_filename(const std::string& name) {
        int start = name.find('/') == std::string::npos ? 0 : name.find_last_of('/') + 1;
		return name.substr(start, name.find_last_of(".") - start);
	}

	std::string read_file(const std::string& file) {
		std::fstream fi(file);
		std::string res;
		for (std::string line; std::getline(fi, line);) {
			res += line + "\n";
		}
		return res;
	}

	std::string diff(const std::string& a, const std::string& b) {
		fclose(popen(format("diff -Z %s %s > " + JUDGE_DIFF_OUT_ANS, a.data(), b.data()).data(), "r"));

		return read_file(JUDGE_DIFF_OUT_ANS);;
	}
	
	std::vector<std::string> get_directory_entries(const std::string& dir) {
		std::vector<std::string> filenames;
		for (auto& entry: std::experimental::filesystem::directory_iterator(dir)) {
			filenames.push_back(entry.path().filename());
		}
		return filenames;
	}

    std::vector<Test> get_tests(const std::string& test_path, const std::string& inp_ext, const std::string& ans_ext) {
		std::set<std::string> ins, anss;
		for (auto& fn: helper::get_directory_entries(test_path)) {
			auto raw = helper::raw_filename(fn);
			auto ext = helper::extension(fn);
			if (ext == inp_ext) {
				ins.emplace(raw);
			}
			if (ext == ans_ext) {
				anss.emplace(raw);
			}
		}

		std::vector<std::string> test_names;
		std::set_intersection(ins.begin(), ins.end(), anss.begin(), anss.end(), std::back_inserter(test_names));

        std::vector<Test> res;
        for (const auto& test_name: test_names) {
            res.push_back(Test {test_path, test_name, inp_ext, ans_ext});
        }

		return res;
	}
    
    void make_dir(const std::string& dir) {
        fclose(popen(("mkdir -p " + dir).data(), "r"));
    }

    void make_dirs() {
		make_dir(JUDGE_DIR);
		make_dir(JUDGE_BIN);
	}

	void clean() {
		fclose(popen("rm -rf " JUDGE_DIR " 2> /dev/null", "r"));
		fclose(popen("rm -R __pycache__ 2> /dev/null", "r"));
	}
}
