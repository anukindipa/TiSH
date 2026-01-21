#include "shell.h"

////////////////////////////////////////////////////////////////////////////
// handle a given command input
////////////////////////////////////////////////////////////////////////////

void command_handler(std::string input, const std::set<std::string>& PATH_DIRS,
                     const std::set<std::string>& commands) {
    if (input == "exit") {
        exit(0);
    }

    if (input.substr(0, 4) == "echo") {
        if (input.length() <= 5) {
            std::cout << std::endl;
            return;
        }
        std::cout << input.substr(5) << std::endl;
        return;
    }

    if (input.substr(0, 4) == "type") {
        if (input.length() <= 5) {
            std::cout << std::endl;
            return;
        }
        type_cmd(input.substr(5), PATH_DIRS, commands);
        return;
    }

    std::cout << input << ": command not found" << std::endl;
    return;
}

////////////////////////////////////////////////////////////////////////////
// for a given command, type whether it's a shell builtin, or executable
////////////////////////////////////////////////////////////////////////////
void type_cmd(std::string command, const std::set<std::string>& PATH_dirs,
              const std::set<std::string>& commands) {
    // check builtin commands
    if (commands.find(command) != commands.end()) {
        std::cout << command << " is a shell builtin" << std::endl;
        return;
    }

    // check PATH commands
    std::filesystem::path cmd_path = command_exists_in_PATH(command, PATH_dirs);
    if (!cmd_path.empty()) {
        std::cout << command << " is " << cmd_path.string() << std::endl;
        return;
    }

    std::cout << command << ": not found" << std::endl;
}
