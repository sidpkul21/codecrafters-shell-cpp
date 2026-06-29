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
        }
        else {
            bool print_status = false;
            if(builtin.findfile(command.name, print_status)) {
                std::system(command.input.c_str());
            } else {
                //std::cout << command.input << ": command not found" << std::endl;
                std::string err_msg = command.input + ": command not found";
                builtin.printError(err_msg, command);
                err_msg.clear();
            }
        }
    }

}

void Shell::print_prompt() const {
    std::cout << "$ ";
}
