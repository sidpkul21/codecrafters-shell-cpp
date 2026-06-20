#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;


  while(true) {
    // TODO: Uncomment the code below to pass the first stage
    std::cout << "$ ";

    //Handling invalid prompts
    std::string command;
    std::getline(std::cin, command);
    if(command == "exit") {
      break;
    } else if(command == "pwd") {
      std::cout<<std::system("cd")<<std::endl;
    } else if(command.substr(0, 5) == "echo ") {
      std::cout<<command.substr(5)<<std::endl;
    } else if(command.substr(0, 5) == "type ") {
      if(command.substr(5) == "echo" | command.substr(5) == "exit" | command.substr(5) == "type") {
        std::cout<<command.substr(5)<<" is a shell builtin"<<std::endl;
      } else {
        bool path_found = 0;
        std::string path = getenv("PATH");
        std::istringstream ss(path);
        std::string directory;
        while(getline(ss, directory, ':')) {
          std::string fullpath = directory + "/" + command.substr(5);
          if(!access(fullpath.c_str(), X_OK)) {
            std::cout<<command.substr(5)<<" is "<<fullpath<<std::endl;
            path_found = 1;
            break;
          }
        }
        if(!path_found) {
          std::cout<<command.substr(5)<<": not found"<<std::endl;
        }
      }
    } else {
      bool path_found = 0;
      
      std::istringstream ss1(command);
      std::string file;
      getline(ss1, file, ' ');

      std::string path = getenv("PATH");
      std::istringstream ss2(path);
      std::string directory;

      while(getline(ss2, directory, ':')){
        std::string fullpath = directory + '/' + file;
        if(!access(fullpath.c_str(), X_OK)) {
          path_found = 1;
          std::system(command.c_str());
          break;
        }
      }
      if(!path_found) {
        std::cout<<command<<": command not found"<<std::endl;
      }
    }
  }

}
