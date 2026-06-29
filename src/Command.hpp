#pragma once

#include <string>
#include <vector>

struct Command {
    std::string name;
    std::vector<std::string> args;
    std::string input;
    std::string redirect_target;
    std::string redirect_error;
};