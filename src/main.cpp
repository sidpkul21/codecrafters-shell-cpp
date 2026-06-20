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
    } else if(command.substr(0, 5) == "echo ") {
      std::cout<<command.substr(5)<<std::endl;
    } else if(command.substr(0, 5) == "type ") {
      if(command.substr(5) == "echo" | command.substr(5) == "exit" | command.substr(5) == "type") {
        std::cout<<command.substr(5)<<" is a shell builtin"<<std::endl;
      } else {
        std::string path = getenv("PATH");
        std::istringstream ss(path);
        std::string directory;
        bool found = 0;
        while(getline(ss, directory, ':')) {
          const std::string fullpath = directory + "/" + command.substr(5);
          if(access(fullpath.c_str(), X_OK) == 0) {
            std::cout<<command.substr(5)<<" is "<<fullpath<<std::endl;
            found = 1;
            break;
          }
        }
        if(!found) {
          std::cout<<command.substr(5)<<": not found"<<std::endl;
        }
      }
    } else {
      std::cout<<command<<": command not found"<<std::endl;
    }
  }

}
