#include "Command.hpp"
#include <string>

class Parser{
public:
    Command parse(const std::string& input) const;
};
