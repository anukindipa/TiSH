#include "shell.h"

std::string get_first_word(const std::string& full_string) {
    std::string first_word;

    // Find the position of the first space character
    size_t space_pos = full_string.find(' ');

    // Check if a space was found
    if (space_pos != std::string::npos) {
        // Extract the substring from the beginning (index 0) to the first space
        first_word = full_string.substr(0, space_pos);
    } else {
        // If no space is found, the whole string is one word
        first_word = full_string;
    }
    return first_word;
}

std::vector<char*> tokenize(const std::string& text) {
    std::stringstream ss(text);
    std::string token;
    std::vector<char*> tokens;

    while (std::getline(ss, token, ' ')) {
        if (!token.empty()) {
            char* arg = new char[token.size() + 1];
            std::strcpy(arg, token.c_str());
            tokens.push_back(arg);
        }
    }
    return tokens;
}