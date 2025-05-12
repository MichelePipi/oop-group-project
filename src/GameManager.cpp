#include "GameManager.hpp"

GameManager::GameManager()
    : cookies(0), manualClicker(std::make_unique<ManualClicker>()) {
    generators.emplace_back(std::make_unique<Factory>());
    generators.emplace_back(std::make_unique<Grandma>());
    generators.emplace_back(std::make_unique<Autoclicker>());
}

void GameManager::startGame() {
    int choice;
    do {
        runAutoGeneration();
        displayMenu();
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }
        handleChoice(choice);
    } while (choice != 0);
}

void GameManager::displayMenu() {
    std::cout << "\n=== Cookie Clicker Menu ===\n";
    std::cout << "Cookies: " << cookies << "\n";
    std::cout << "[1] Click Cookie\n";
    std::cout << "[2] Buy Factory\n";
    std::cout << "[3] Buy Grandma\n";
    std::cout << "[4] Buy Autoclicker\n";
    std::cout << "[5] View Generators\n";
    std::cout << "[6] Save Game\n";
    std::cout << "[7] Load Game\n";
    std::cout << "[8] View Stats\n";
    std::cout << "[0] Exit\n";
    std::cout << "Choice: ";
}

void GameManager::handleChoice(int choice) {
    switch (choice) {
        case 1:
            manualClicker->generate(cookies);
            stats.registerClick();
            stats.addCookies(1);
            break;
        case 2:
        case 3:
        case 4: {
            int index = choice - 2;
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
            showGenerators();
            break;
        case 6:
            saveGame();
            break;
        case 7:
            loadGame();
            break;
        case 8:
            stats.printStats();
            break;
        case 0:
            std::cout << "Exiting game.\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
    }
}

void GameManager::showGenerators() {
    for (const auto& g : generators) {
        std::cout << g->getStatus() << "\n";
    }
}

void GameManager::runAutoGeneration() {
    for (auto& g : generators) {
        int before = cookies;
        g->generate(cookies);
        stats.addCookies(cookies - before);
    }
}

void GameManager::saveGame() {
    std::ofstream out("save.txt");
    out << cookies << "\n";
    for (const auto& g : generators) {
        out << g->getLevel() << "\n";
    }
    std::cout << "Game saved successfully.\n";
}

void GameManager::loadGame() {
    std::ifstream in("save.txt");
    if (!in) {
        std::cout << "No save file found.\n";
        return;
    }

    in >> cookies;
    for (auto& g : generators) {
        int level;
        in >> level;
        for (int i = 0; i < level; ++i) g->increaseLevel();
    }
    std::cout << "Game loaded!\n";
 
}

int GameManager::getCookieCount() const {
    return cookies;
}

float GameManager::calculateTotalCps() const {
    float total = 0.f;
    for (const auto& g : generators) {
        total += g->getCps();
    }
    return total;
}

int GameManager::getGeneratorLevel(int index) const {
    return generators[index]->getLevel();
}

int GameManager::getGeneratorCost(int index) const {
    return generators[index]->getCost();
}
