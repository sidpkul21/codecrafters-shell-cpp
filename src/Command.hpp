#pragma once

#include <string>
#include <vector>

enum class rdOps {
    op_stderr,
    op_stdout
};

struct Redirect {
    rdOps op;
    bool append;
    std::string target = NULL;
};


struct Command {
    std::string name;
    std::vector<std::string> args;
    std::string input;
    Redirect redirect;
};