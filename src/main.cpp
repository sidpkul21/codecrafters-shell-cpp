#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <filesystem>
#include "Shell.hpp"

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  Shell shell;
  shell.run();
}
