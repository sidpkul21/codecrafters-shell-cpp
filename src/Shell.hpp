#pragma once
#include <unistd.h>

class Shell{
public:
    void run();
private:
    void print_prompt() const;
};