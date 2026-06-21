#include "Shell.hpp"
#include "Parser.hpp"
#include "Builtin.hpp"
#include <string>
#include <iostream>

void Shell::run() {
    while(true) {
        
        print_prompt();

        std::string input;
        if(!std::getline(std::cin, input)) {
            break;
        }
        
        Parser parser;
        Command command = parser.parse(input);

        if(command.name == "exit") {
            break;
        }

        Builtin builtin;
        if(builtin.isBuiltin(command)) {
            builtin.execute(command);
        } else {
            std::cout<<command.name<<": command not found"<<std::endl;
        }
        
    }

}

void Shell::print_prompt() const {
    std::cout << "$ ";
}
