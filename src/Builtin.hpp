#pragma once
#include "Command.hpp"

class Builtin{
    public:
        bool isBuiltin(const Command& command) const;
        bool execute(const Command& command) const;
};