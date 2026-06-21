#include <string>
#include "Builtin.hpp"
#include <iostream>
#include <filesystem>
#include <unistd.h>

bool Builtin::isBuiltin(const Command& command) const{
    return command.name == "pwd"  ||
           command.name == "echo" ||
           command.name == "type";
}

bool Builtin::execute(const Command& command) const{
    if(command.name == "echo") {
        for(const auto& elem:command.args) {
            std::cout << elem;
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

        std::string path = getenv("PATH");
        std::istringstream ss(path);
        std::string directory;

        while(getline(ss, directory, ':')) {
          std::string fullpath = directory + "/" + type_arg;
          if(!access(fullpath.c_str(), X_OK)) {
            std::cout << type_arg <<" is "<< fullpath << std::endl;
            return true;
          }
        }

        std::cout << type_arg << ": not found" <<std::endl;
        return true;
    }

    std::string filename = command.name;
    std::string path = getenv("PATH");
    std::istringstream ss2(path);
    std::string directory;

    while(getline(ss2, directory, ':')){
        std::string fullpath = directory + '/' + filename;
        if(!access(fullpath.c_str(), X_OK)) {
            std::system(command.input.c_str());
            return true;
        }
      }
    
    std::cout << command.input.c_str() << ": command not found" << std::endl;
    return true;
}