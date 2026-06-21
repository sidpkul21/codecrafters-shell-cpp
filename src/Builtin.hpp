#pragma once
#include "Command.hpp"

class Bulletin{
    public:
        bool isBulletin(const Command& command) const;
        bool execute(const Command& command) const;
};