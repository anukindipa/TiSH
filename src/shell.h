//////////////////////////////////////////////////////////////////////////////
// Imports
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// function declarations for command handling
//////////////////////////////////////////////////////////////////////////////

// handle a given command input
void command_handler(std::string input, const std::set<std::string>& PATH_DIRS,
                     const std::set<std::string>& commands);

// for a given command, type whether it's a shell builtin, or executable
void type_cmd(std::string command, const std::set<std::string>& PATH_dirs,
              const std::set<std::string>& commands);

//////////////////////////////////////////////////////////////////////////////
// function declarations for path utilities
//////////////////////////////////////////////////////////////////////////////

// used to generate directories from PATH env variable
std::set<std::string> _PATH_dirs();

// check if command exists in given directory
std::filesystem::path command_exists_in_dir(const std::string& command,
                                            const std::filesystem::path& dir);

// check if command exists in any of the PATH directories
std::filesystem::path command_exists_in_PATH(
    const std::string& command, const std::set<std::string>& PATH_dirs);