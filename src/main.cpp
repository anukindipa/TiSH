#include "shell.h"

std::set<std::string> commands = {"echo", "type", "exit"};
std::set<std::string> PATH_DIRS = _PATH_dirs();

// Read-Eval-Print Loop
// Main Loop for the shell
void repl() {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);

    if (!input.empty()) {
        command_handler(input, PATH_DIRS, commands);
        return;
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
