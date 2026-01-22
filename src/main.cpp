#include "shell.h"

// All the builtin commands
std::vector<std::string> commands = {"echo", "type", "exit", "pwd"};

// All the directory in the PATH environemntal variable
std::vector<std::string> PATH_DIRS = _PATH_dirs();

// Read-Eval-Print Loop
// Main Loop for the shell
void repl() {
    // the shell will have a > at each new line similar to `anuk@laptop ~` in bash 
    std::cout << "> ";

    // read a line
    std::string input;
    std::getline(std::cin, input);

    if (!input.empty()) {
        command_handler(input, PATH_DIRS, commands);
    }
}

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while (true) {
        repl();
    }
}
