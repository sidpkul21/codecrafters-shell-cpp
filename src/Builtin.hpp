#pragma once
#include "Command.hpp"
#include <string>

class Builtin{
    public:
        bool isBuiltin(const Command& command) const;
        bool execute(const Command& command) const;
        bool findfile(const std::string& file, bool print) const;
};