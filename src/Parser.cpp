#include "Parser.hpp"
#include <string>
#include <sstream>
#include <iostream>

namespace {

    std::vector<std::string> tokenizer(const std::string& input) {
        std::vector<std::string> tokens;
        bool isbuildingtoken = false;
        bool issquote = false;
        bool isdquote = false;
        std::string curr;
        curr.clear();
        
        for(char c: input) {
            if(c == '"') {
                isdquote = !isdquote;
                isbuildingtoken = true;
            } else if(c == '\'' && !isdquote) {
                issquote = !issquote;
                isbuildingtoken = true;
            } else if(std::isspace(static_cast<unsigned char>(c)) && (!issquote && !isdquote)) {
                if(isbuildingtoken) {
                    tokens.push_back(curr);
                    curr.clear();
                    isbuildingtoken = false;
                }
            } else {
                curr += c;
                isbuildingtoken = true;
            }
        }

        if(isbuildingtoken) {
            tokens.push_back(curr);
            curr.clear();
        }

        return tokens;
    }
}

Command Parser::parse(const std::string& input) const{
    Command command;
    command.input = input;
    
    auto tokens = tokenizer(input);
    
    if(tokens.empty()) {
        return command;
    }

    command.name = tokens[0];

    for(size_t i = 1; i < tokens.size(); i ++) {
        command.args.push_back(tokens[i]);
    }
    
    return command;
}