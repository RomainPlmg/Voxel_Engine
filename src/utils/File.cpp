//
// Created by Romain on 21/12/2024.
//

#include "File.h"

#include "Log.h"

std::string File::ReadFromFile(const std::string& filePath) {
    std::ifstream stream(filePath);

    if (!stream.is_open()) {
        FATAL_MSG("File \'{0}\' not found.", filePath);
    }

    std::string line;
    std::stringstream ss;
    while (getline(stream, line)) {
        ss << line << '\n';
    }
    return ss.str();
}