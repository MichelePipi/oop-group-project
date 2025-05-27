// SaveFileManager.cpp
// Handles saving and loading game state to/from text files using simple file dialogs.

#include "SaveFileManager.hpp"
#include <iostream>
#include <string>
#include <random>
#include <memory>
#include <fstream>
#include "../include/portable-file-dialogs.h"
#include "AutoGenerator.hpp"

// Constructor (currently does nothing special)
SaveFileManager::SaveFileManager() {}

// Destructor (also currently empty, but included for completeness)
SaveFileManager::~SaveFileManager() {}

// Saves the game state to a uniquely named text file
void SaveFileManager::saveFile(long long cookies, const std::vector<std::unique_ptr<AutoGenerator>>& generators, bool hasGoldenCookieDough) {
    std::ofstream Save(this->generateFileName() + ".txt"); // Create file with a unique name
    Save << cookies << std::endl;                          // Save total cookies
    Save << generators[0]->getLevel() << std::endl;        // Factory level
    Save << generators[1]->getLevel() << std::endl;        // Grandma level
    Save << generators[2]->getLevel() << std::endl;        // Autoclicker level
    Save << (hasGoldenCookieDough ? 1 : 0) << std::endl;   // Golden dough owned = 1, not owned = 0
    Save.close();                                          // Close file
}

// Utility function to check if a string is a number
bool is_number(const std::string& s, double& out) {
    std::istringstream iss(s);
    iss >> out;
    return !(iss.fail() || !iss.eof());
}

// Loads a game state from a selected text file
std::vector<double> SaveFileManager::loadFile() {
    std::vector<double> numbers;

    // Show open file dialog and get selected file
    auto selection = pfd::open_file("Select a Save File", ".", { "Save Files (*.txt *.sav)", "*.txt *.sav" }).result();

    if (!selection.empty()) {
        std::ifstream file(selection[0]);
        if (!file) {
            std::cerr << "Failed to open file.\n";
            return {};
        }

        std::string line;
        int lineCount = 0;

        // Read and validate up to 5 lines from file
        while (lineCount < 5 && std::getline(file, line)) {
            std::cout << "Read: " << line << std::endl;
            double value;
            if (!is_number(line, value)) {
                std::cerr << "Invalid number on line " << (lineCount + 1) << ": " << line << "\n";
                return {};
            }
            numbers.push_back(value);
            ++lineCount;
        }

        // Ensure 5 lines were read
        if (lineCount < 5) {
            std::cerr << "File contains fewer than 5 lines.\n";
            return {};
        }

        file.close();
        return numbers;
    }

    std::cout << "No file selected.\n";
    return {};
}

// Generates a random UUID-like string to use as a file name
std::string SaveFileManager::generateFileName() {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    std::string res;
    for (int i = 0; i < 16; i++) {
        if (dash[i]) res += "-";           // Insert dash at UUID-style positions
        res += v[dist(rng)];               // Random hex digit
        res += v[dist(rng)];
    }

    return res;
}
