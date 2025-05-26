//
// Created by Michele Antonio Pipicelli on 25/5/2025.
//

#ifndef SAVEFILEMANAGER_HPP
#define SAVEFILEMANAGER_HPP
#include <string>
#include <vector>
#include <memory>
#include "AutoGenerator.hpp"


class SaveFileManager {
    public:
        SaveFileManager();
        ~SaveFileManager();
        void saveFile(long long cookies, const std::vector<std::unique_ptr<AutoGenerator>>& generators, bool hasGoldenCookieDough);
        std::vector<double> loadFile();
        std::string generateFileName();
};

#endif //SAVEFILEMANAGER_HPP
