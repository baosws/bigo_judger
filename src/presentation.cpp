#include "presentation.h"

namespace presentation {
    std::string color_string(const std::string& str, const Color& color) {
        static std::map<Color, const char*> color_begin = {
            {Red, "\033[0;31m"},
            {Green, "\033[0;36m"},
            {Yellow, "\033[1;33m"},
            {Purple, "\033[0;35m"},
            {White, "\033[1;37m"},
			{Orange, "\033[1;31m"}
        };
        static const char* nc = "\033[0m";

        return color_begin[color] + str + nc;
    }
}
