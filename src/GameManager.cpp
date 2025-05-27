#include "GameManager.hpp"
#include "Action.hpp"

// Constructor:
// Initializes cookie count to 0 and sets up the manual clicker.
// Also adds all available AutoGenerators (Factory, Grandma, Autoclicker) to the vector.
GameManager::GameManager()
    : cookies(0), manualClicker(std::make_unique<ManualClicker>()) {
    generators.emplace_back(std::make_unique<Factory>());
    generators.emplace_back(std::make_unique<Grandma>());
    generators.emplace_back(std::make_unique<Autoclicker>());
}

// Handles user choices from the menu.
// Handles clicking, buying generators, showing stats, saving, and quitting.
void GameManager::handleChoice(int choice) {
    switch (choice) {
        case CLICKED_COOKIE:
            // User manually clicked for cookies
            manualClicker->generate(1);
            stats.registerClick(); // updates total click count
            stats.addCookies(1LL); // updates total cookie count
            cookies += 114192; // TEMP VALUE for debugging or a joke maybe? Consider fixing
            break;

        case BUY_FACTORY:
        case BUY_GRANDMA:
        case BUY_AUTOCLICKER: {
            // Handles purchase of one of the generators
            int index = choice - 2; // Assumes factory=2, grandma=3, autoclicker=4
            if (cookies >= generators[index]->getCost()) {
                cookies -= generators[index]->getCost();
                generators[index]->increaseLevel();
                std::cout << "Bought " << generators[index]->getName() << "!\n";
            } else {
                std::cout << "Not enough cookies!\n";
            }
            break;
        }

        case 5:
            // Show current status of all generators
            showGenerators();
            break;

        case 6:
            // Display gameplay statistics
            stats.printStats();
            break;

        case SAVE_FILE:
            // Save game state to file
            saveFile.saveFile(cookies, generators, hasGoldenDough);
            break;

        case BUY_GOLDEN_DOUGH:
            // One-time upgrade that doubles CPS from all generators
            if (hasGoldenDough) return;
            if (cookies >= 500) {
                hasGoldenDough = true;
                cookies -= 500;
            }
            break;

        case 0:
            // Exit the game
            std::cout << "Exiting game.\n";
            break;

        default:
            // Invalid menu option
            std::cout << "Invalid choice.\n";
            break;
    }
}

// Displays each generator's current status: name, level, and CPS
void GameManager::showGenerators() {
    for (const auto& g : generators) {
        std::cout << g->getStatus() << "\n";
    }
}

// Runs auto-generation for each generator once per tick/frame
// Adds generated cookies to total and updates stats
void GameManager::runAutoGeneration() {
    for (auto& g : generators) {
        int before = cookies;
        g->generate(cookies);
        stats.addCookies(cookies - before); // track how much was generated
    }
}

// Returns current cookie count
int GameManager::getCookieCount() const {
    return cookies;
}

// Calculates total cookies per second from all generators
// If Golden Dough is owned, doubles total CPS
float GameManager::calculateTotalCps() const {
    float total = 0.f;
    for (const auto& g : generators) {
        total += g->getCps();
    }
    if (hasGoldenDough) return total * 2;
    return total;
}

// Gets the current level of a generator by index (used for display/UI)
int GameManager::getGeneratorLevel(int index) const {
    return generators[index]->getLevel();
}

// Gets the current cost of a generator by index (used for display/UI)
int GameManager::getGeneratorCost(int index) const {
    return generators[index]->getCost();
}

// Allows manual setting of the cookie count (e.g. loading from file)
void GameManager::setCookies(long long c) {
    cookies = c;
}
