//
// Created by Michele Antonio Pipicelli on 25/5/2025.
//

#include "SaveFileManager.hpp"
#include <iostream>
#include <string>
#include <random>
#include <memory>
#include <fstream>
#include "../include/portable-file-dialogs.h"

#include "AutoGenerator.hpp"

SaveFileManager::SaveFileManager() {
}

SaveFileManager::~SaveFileManager() {
}

void SaveFileManager::saveFile(long long cookies, const std::vector<std::unique_ptr<AutoGenerator>>& generators) {
    std::ofstream Save(this->generateFileName() + ".txt");
    Save << cookies << std::endl;
    Save << generators[0]->getLevel() << std::endl;
    Save << generators[1]->getLevel() << std::endl;
    Save << generators[2]->getLevel() << std::endl;
    // TODO: Add the total cookies earnt
    // Save << "test";
    Save.close();
}

bool is_number(const std::string& s, double& out) {
    std::istringstream iss(s);
    iss >> out;
    return !(iss.fail() || !iss.eof());
}

std::vector<double> SaveFileManager::loadFile() {
    std::vector<double> numbers;

    auto selection = pfd::open_file("Select a Save File", ".", { "Save Files (*.txt *.sav)", "*.txt *.sav" }).result();

    if (!selection.empty()) {
        std::ifstream file(selection[0]);
        if (!file) {
            std::cerr << "Failed to open file.\n";
            return {};
        }

        std::string line;
        int lineCount = 0;
        while (lineCount < 4 && std::getline(file, line)) {
            std::cout << "Read: " << line << std::endl;
            double value;
            if (!is_number(line, value)) {
                std::cerr << "Invalid number on line " << (lineCount + 1) << ": " << line << "\n";
                return {};
            }
            numbers.push_back(value);
            ++lineCount;
        }

        if (lineCount < 4) {
            std::cerr << "File contains fewer than 4 lines.\n";
            return {};
        }

        file.close();
        return numbers;
    } else {
        std::cout << "No file selected.\n";
        return {};
    }
}

bool SaveFileManager::isValidFloat(const std::string &s, float &result) {
}

std::string SaveFileManager::generateFileName() {
    static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    std::string res;
    for (int i = 0; i < 16; i++) {
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }

    return res;
}
