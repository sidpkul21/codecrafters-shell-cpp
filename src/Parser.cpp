#include "Parser.hpp"
#include <string>
#include <sstream>

namespace {
    std::vector<std::string> tokenizer(const std::string& input) {
        
        std::vector<std::string> tokens;
        std::string current;

        bool isquote = false;
        bool isbuildingtoken = false;
        
        for(char c: input) {
            if(c == '\'') {
                isquote = !isquote;
                isbuildingtoken = true;
            } else if(static_cast<unsigned char>(c) && !isquote) {
                if(isbuildingtoken) {
                    tokens.push_back(current);
                    current.clear();
                    isbuildingtoken = false;
                }
            } else {
                current += c;
                isbuildingtoken = true;
            }
        }

        if(isbuildingtoken) {
            tokens.push_back(current);
        }

        return tokens;
    } 
}

Command Parser::parse(const std::string& input) const{
    Command command;
    
    auto tokens = tokenizer(command.input);
    
    if(tokens.empty()) {
        return command;
    }

    command.name = tokens[0];

    for(size_t i = 0; i < tokens.size(); i ++) {
        command.args.push_back(tokens[i]);
    }
    
    return command;
}