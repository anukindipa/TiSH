//////////////////////////////////////////////////////////////////////////////
// Imports
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;
//////////////////////////////////////////////////////////////////////////////
// functions in (src/main.cpp)
//////////////////////////////////////////////////////////////////////////////

// Read-Eval-Print Loop
// Main Loop for the shell
void repl();

//////////////////////////////////////////////////////////////////////////////
// utility function declarations (src/utils.cpp)
//////////////////////////////////////////////////////////////////////////////

// Get the first word in a string
// used to find command from user input
std::string get_first_word(const std::string& full_string);

// convert a string to a vector of c style strings 
// to be used by execv() and cd
std::vector<char*> tokenize(const std::string& text);

//////////////////////////////////////////////////////////////////////////////
// function declarations for command handling (src/commands.cpp)
//////////////////////////////////////////////////////////////////////////////

// handle a given command input
void command_handler(std::string input,
                     const std::vector<std::string>& PATH_DIRS,
                     const std::vector<std::string>& commands);

// for a given command, type whether it's a shell builtin, or executable
void type_cmd(std::string command, const std::vector<std::string>& PATH_dirs,
              const std::vector<std::string>& commands);

// Execute executable commands in PATH
void exec_PATH_cmd(std::string input, const char* cmd_path);

//////////////////////////////////////////////////////////////////////////////
// function declarations for path utilities (src.path_utils.cpp)
//////////////////////////////////////////////////////////////////////////////

// used to generate directories from PATH env variable
std::vector<std::string> _PATH_dirs();

// check if command exists in given directory
fs::path command_exists_in_dir(const std::string& command, const fs::path& dir);

// check if command exists in any of the PATH directories
fs::path command_exists_in_PATH(const std::string& command,
                                const std::vector<std::string>& PATH_dirs);
