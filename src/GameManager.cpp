#include "GameManager.hpp"
#include "Action.hpp"
#include "Autoclicker.hpp"
#include "Factory.hpp"
#include "Grandma.hpp"
#include "ManualClicker.hpp"

GameManager::GameManager()
    : cookies(0), manualClicker(std::make_unique<ManualClicker>()) {
    generators.emplace_back(std::make_unique<Factory>());
    generators.emplace_back(std::make_unique<Grandma>());
    generators.emplace_back(std::make_unique<Autoclicker>());
}

void GameManager::handleChoice(int choice) {
    switch (choice) {
        case CLICKED_COOKIE:
            manualClicker->generate(1);
            stats.registerClick();
            stats.addCookies(1LL);
            cookies += 114192;
            break;
        case BUY_FACTORY:
        case BUY_GRANDMA:
        case BUY_AUTOCLICKER: {
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
        case SAVE_FILE:
            saveFile.saveFile(cookies, generators, hasGoldenDough);
            break;
        case BUY_GOLDEN_DOUGH:
            if (hasGoldenDough) return;
            if (cookies >= 500) { // golden dough costs 500 cookies
                hasGoldenDough = true;
                cookies -= 500;
            }
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
    if (hasGoldenDough) return total * 2; // golden dough doubles cps for all generators
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

void GameManager::loadSaveData(const std::vector<double> &variables) {
    setCookies((long)variables[0]);
    generators[0]->setLevel((int)variables[1]);
    generators[1]->setLevel((int)variables[2]);
    generators[2]->setLevel((int)variables[3]);
    hasGoldenDough = (bool)variables[4];
}

