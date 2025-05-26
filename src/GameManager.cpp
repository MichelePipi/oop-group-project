#include "GameManager.hpp"

GameManager::GameManager()
    : cookies(0), manualClicker(std::make_unique<ManualClicker>()) {
    generators.emplace_back(std::make_unique<Factory>());
    generators.emplace_back(std::make_unique<Grandma>());
    generators.emplace_back(std::make_unique<Autoclicker>());
}


void GameManager::handleChoice(int choice) {
    switch (choice) {
        case 1:
            manualClicker->generate(1);
            stats.registerClick();
            stats.addCookies(1LL);
            cookies += 1;
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
            stats.printStats();
            break;
        case 9:
            saveFile.saveFile(cookies, generators);
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

void GameManager::setCookies(long long c) {
    cookies = c;
}

