#include "Parser.hpp"
#include <string>
#include <sstream>

Command Parser::parse(const std::string& input) const{
    Command command;

    command.input = input;

    std::istringstream ss(input);
    
    ss >> command.name;

    std::string arg;
    while(ss >> arg) {
        command.args.push_back(arg);
    }
    
    return command;
}