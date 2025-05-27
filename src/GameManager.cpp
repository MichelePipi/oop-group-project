#include "GameManager.hpp"
#include "Action.hpp"
#include "Autoclicker.hpp"
#include "Factory.hpp"
#include "Grandma.hpp"
#include "ManualClicker.hpp"

// Constructor:
// Initializes the game state with 0 cookies and sets up all generators.
// ManualClicker is created, and AutoGenerators (Factory, Grandma, Autoclicker) are added to the list.
GameManager::GameManager()
    : cookies(0), manualClicker(std::make_unique<ManualClicker>()) {
    generators.emplace_back(std::make_unique<Factory>());
    generators.emplace_back(std::make_unique<Grandma>());
    generators.emplace_back(std::make_unique<Autoclicker>());
}

// Handles all menu choices from the player.
void GameManager::handleChoice(int choice) {
    switch (choice) {

        // Manual click: generates 1 cookie and updates stats
        case CLICKED_COOKIE:
            manualClicker->generate(1); // Adds 1 cookie (but note: by value)
            stats.registerClick();      // Increments total click count
            stats.addCookies(1LL);      // Adds to total cookies earned
            cookies += 1;
            break;

        // Handles buying any of the three generators (factory, grandma, autoclicker)
        case BUY_FACTORY:
        case BUY_GRANDMA:
        case BUY_AUTOCLICKER: {
            int index = choice - 2; // Assumes ordering: 2=Factory, 3=Grandma, 4=Autoclicker
            if (cookies >= generators[index]->getCost()) {
                cookies -= generators[index]->getCost();
                generators[index]->increaseLevel();
                std::cout << "Bought " << generators[index]->getName() << "!\n";
            } else {
                std::cout << "Not enough cookies!\n";
            }
            break;
        }

        // Display all generator statuses
        case 5:
            showGenerators();
            break;

        // Display gameplay stats
        case 6:
            stats.printStats();
            break;

        // Save game to file
        case SAVE_FILE:
            saveFile.saveFile(cookies, generators, hasGoldenDough);
            break;

        // Purchase Golden Dough upgrade (one-time, doubles CPS)
        case BUY_GOLDEN_DOUGH:
            if (hasGoldenDough) return;
            if (cookies >= 500) {
                hasGoldenDough = true;
                cookies -= 500;
            }
            break;

        // Quit game
        case 0:
            std::cout << "Exiting game.\n";
            break;

        // Fallback for invalid inputs
        default:
            std::cout << "Invalid choice.\n";
            break;
    }
}

// Displays the name, level, and CPS for each generator
void GameManager::showGenerators() {
    for (const auto& g : generators) {
        std::cout << g->getStatus() << "\n";
    }
}

// Triggers cookie generation from all AutoGenerators based on their CPS
// Adds generated amount to cookies and updates stats
void GameManager::runAutoGeneration() {
    for (auto& g : generators) {
        int before = cookies;
        g->generate(cookies);
        stats.addCookies(cookies - before);
    }
}

// Returns the current cookie count
int GameManager::getCookieCount() const {
    return cookies;
}

// Calculates total CPS from all generators
// If Golden Dough is active, total is doubled
float GameManager::calculateTotalCps() const {
    float total = 0.f;
    for (const auto& g : generators) {
        total += g->getCps();
    }
    if (hasGoldenDough) return total * 2;
    return total;
}

// Returns the level of a generator by index
int GameManager::getGeneratorLevel(int index) const {
    return generators[index]->getLevel();
}

// Returns the current cost of a generator by index
int GameManager::getGeneratorCost(int index) const {
    return generators[index]->getCost();
}

// Sets the cookie count (e.g., used when loading saved data)
void GameManager::setCookies(long long c) {
    cookies = c;
}

// Loads saved data into game state
// Expects a vector of values: [cookies, factory level, grandma level, autoclicker level, hasGoldenDough]
void GameManager::loadSaveData(const std::vector<double> &variables) {
    setCookies(static_cast<long long>(variables[0]));
    generators[0]->setLevel(static_cast<int>(variables[1])); // Factory
    generators[1]->setLevel(static_cast<int>(variables[2])); // Grandma
    generators[2]->setLevel(static_cast<int>(variables[3])); // Autoclicker
    hasGoldenDough = static_cast<bool>(variables[4]);        // Golden Dough flag
}
