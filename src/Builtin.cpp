#include <string>
#include "Builtin.hpp"
#include <iostream>
#include <filesystem>
#include <unistd.h>

bool Builtin::isBuiltin(const Command& command) const{
    return command.name == "pwd"  ||
           command.name == "echo" ||
           command.name == "type" ||
           command.name == "cd";
}

bool Builtin::execute(const Command& command) const{
    if(command.name == "echo") {
        for(const auto& elem:command.args) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
        return true;
    } 
    
    if(command.name == "pwd") {
        std::string curr_dir = std::filesystem::current_path().string();
        std::cout << curr_dir << std::endl;
        return true;
    }

    if(command.name == "type") {
        
        std::string type_arg = command.args[0];

        if(type_arg == "echo" | type_arg == "exit" | type_arg == "type" | type_arg == "pwd") {
            std::cout << type_arg << " is a shell builtin" << std::endl;
            return true;
        }

        bool print_status = true;
        if(!findfile(type_arg, print_status)) {
            std::cout << type_arg << ": not found" <<std::endl;
        }

        return true;
    }

    if (command.name == "cd") {
        std::string target_dir = command.args[0];

        if(chdir(target_dir.c_str()) != 0) {
            std::cout << command.name << ": " << target_dir << ": No such file or directory" << std::endl;
        }
        return true;
    }
    
    std::cout << command.input.c_str() << ": command not found" << std::endl;
    return true;
}

bool Builtin::findfile(const std::string& file, bool print) const {
    std::string path = getenv("PATH");
    std::istringstream ss(path);
    std::string directory;

    while(getline(ss, directory, ':')) {
        std::string fullpath = directory + "/" + file;
        if(!access(fullpath.c_str(), X_OK)) {
            if(print) {
                std::cout << file <<" is "<< fullpath << std::endl;
            }
            return true;
        }
    }
    return false;
}