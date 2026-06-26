#include "Parser.hpp"
#include <string>
#include <sstream>
#include <iostream>

namespace {
    std::vector<std::string> tokenizer(const std::string& input) {
        
        std::vector<std::string> tokens;
        std::string current;

        bool isquote = false;
        bool isbuildingtoken = false;
        
        for(char c: input) {
            std::cout<<"print char "<<c<<std::endl;
            if(c == '\'') {
                isquote = !isquote;
                isbuildingtoken = true;
            } else if(std::isspace(static_cast<unsigned char>(c)) && !isquote) {
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
            current.clear();
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
    std::cout<<"command name: "<<command.name<<std::endl;

    for(size_t i = 0; i < tokens.size(); i ++) {
        command.args.push_back(tokens[i]);
        std::cout<<"command name: "<<tokens[i]<<std::endl;
    }
    
    return command;
}