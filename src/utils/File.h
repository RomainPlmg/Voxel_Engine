//
// Created by Romain on 21/12/2024.
//

#ifndef FILE_H
#define FILE_H

#include "pch.h"

class File {
   public:
    static std::string ReadFromFile(const std::string& filePath);
};

#endif  // FILE_H
