#include "shell.h"

////////////////////////////////////////////////////////////////////////////
// handle a given command input
////////////////////////////////////////////////////////////////////////////

void command_handler(std::string input,
                     const std::vector<std::string>& PATH_DIRS,
                     const std::vector<std::string>& commands) {
    // extract first word as command
    std::string cmd = get_first_word(input);

    if (cmd == "exit") {
        exit(0);
    }

    if (cmd == "echo") {
        if (input.length() <= 5) {
            std::cout << std::endl;
            return;
        }
        std::cout << input.substr(5) << std::endl;
        return;
    }

    if (cmd == "type") {
        if (input.length() <= 5) {
            std::cout << std::endl;
            return;
        }
        type_cmd(input.substr(5), PATH_DIRS, commands);
        return;
    }

    if (cmd == "pwd") {
        std::cout << fs::current_path().string() << std::endl;
        return;
    }

    if (cmd == "cd") {
        std::vector<char*> args = tokenize(input);
        std::string new_dir;
        if (args[1] == std::string("~") || args[1] == std::string("") ||
            args.size() == 1) {
            new_dir = getenv("HOME");
        } else {
            new_dir = args[1];
        }
        try {
            // change current path
            fs::current_path(fs::path(new_dir));
        } catch (fs::filesystem_error& e) {
            // print error if path doesn't exist
            std::cout << "cd: " << new_dir << ": No such file or directory"
                      << std::endl;
            return;
        }
        return;
    }

    // run command if its executable in current directory
    fs::path curr_dir_cmd = command_exists_in_dir(cmd, fs::path("."));
    if (!curr_dir_cmd.empty() && cmd.length() > 2 && cmd.substr(0, 2) == "./") {
        // std::cout << "Found command at: " << curr_dir_cmd.string() <<
        // std::endl;
        exec_PATH_cmd(input, curr_dir_cmd.c_str());
        return;
    }

    // if command is in path fork and execute
    fs::path cmd_path = command_exists_in_PATH(cmd, PATH_DIRS);
    if (!cmd_path.empty()) {
        // std::cout << "Found command at: " << cmd_path.string() << std::endl;
        exec_PATH_cmd(input, cmd_path.c_str());
        return;
    }

    std::cout << input << ": command not found" << std::endl;
    return;
}
////////////////////////////////////////////////////////////////////////////
// Execute executable commands in PATH
////////////////////////////////////////////////////////////////////////////
void exec_PATH_cmd(std::string input, const char* cmd_path) {
    pid_t pid = fork();
    if (pid == 0) {
        // child process
        std::vector<char*> args = tokenize(input);
        args.push_back(nullptr);  // null-terminate for execv
        execv(cmd_path, args.data());
        // if execv returns, there was an error
        std::cerr << "Error executing command" << std::endl;
        exit(1);
    } else if (pid > 0) {
        // parent process
        int status;
        // std::cout << "Executing: " << cmd_path << std::endl;
        waitpid(pid, &status, 0);
    } else {
        // fork failed
        std::cerr << "Error forking process" << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////
// for a given command, type whether it's a shell builtin, or executable
////////////////////////////////////////////////////////////////////////////
void type_cmd(std::string command, const std::vector<std::string>& PATH_dirs,
              const std::vector<std::string>& commands) {
    // check builtin commands
    if (std::find(commands.begin(), commands.end(), command) !=
        commands.end()) {
        std::cout << command << " is a shell builtin" << std::endl;
        return;
    }

    // check PATH commands
    fs::path cmd_path = command_exists_in_PATH(command, PATH_dirs);
    if (!cmd_path.empty()) {
        std::cout << command << " is " << cmd_path.string() << std::endl;
        return;
    }
    if (command_exists_in_dir(command, fs::path(".")).empty() == false) {
        std::cout << command << " is " << fs::path(".") / command << std::endl;
        return;
    }

    std::cout << command << ": not found" << std::endl;
}

