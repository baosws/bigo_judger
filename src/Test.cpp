#include "Test.h"
#include "definitions.h"

std::string Test::in() const {
    return path + "/" + name + "." + inp_ext;
}

std::string Test::ans() const {
    return path + "/" + name + "." + ans_ext;
}
