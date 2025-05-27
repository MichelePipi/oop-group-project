#pragma once

// STL and standard includes
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>

// Project includes
#include "ClickableItem.hpp"
#include "ManualClicker.hpp"
#include "AutoGenerator.hpp"
#include "Factory.hpp"
#include "Grandma.hpp"
#include "Autoclicker.hpp"
#include "StatsTracker.hpp"
#include "SaveFileManager.hpp"

// The GameManager class is the central controller for the entire game.
// It manages cookies, user input, generator logic, upgrades, and save/load functionality.
class GameManager {
    
private:
    long long cookies; // Current number of cookies the player has
    std::unique_ptr<ClickableItem> manualClicker; // Pointer to manual clicker object
    StatsTracker stats; // Tracks game stats like total clicks and cookies

public:
    // Constructor: Initializes clicker, stats, and generator list
    GameManager();

    // Flag indicating whether the player owns the Golden Dough upgrade
    bool hasGoldenDough;

    // Holds all automatic generators (Factory, Grandma, Autoclicker)
    std::vector<std::unique_ptr<AutoGenerator>> generators;

    // ---------------------
    // Core Game Functions
    // ---------------------

    // Handles user input/actions from the main menu
    void handleChoice(int choice);

    // Displays status of all generators
    void showGenerators();

    // Executes automatic cookie generation for each generator
    void runAutoGeneration();

    // ---------------------
    // UI / Info Helpers
    // ---------------------

    // Returns current cookie count
    int getCookieCount() const;

    // Calculates and returns total cookies per second (CPS), including upgrades
    float calculateTotalCps() const;

    // Gets cost of a specific generator by index
    int getGeneratorCost(int index) const;

    // Gets current level of a specific generator by index
    int getGeneratorLevel(int index) const;

    // Sets the cookie count (used for loading saved data)
    void setCookies(long long c);

    // SaveFileManager handles saving/loading game data to and from disk
    SaveFileManager saveFile;
};
