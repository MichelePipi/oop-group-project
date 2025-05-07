#include "GameManager.h"
#include "Autoclicker.h"
#include "Grandma.h"
#include "AutoclickerUpgrade.h"
#include "GoldenDoughUpgrade.h"

#include <iostream>
#include <chrono>
#include <thread>

GameManager::GameManager() : totalCookies(0), running(true) {
    // Create Generators
    auto autoclicker = std::make_shared<Autoclicker>();
    auto grandma = std::make_shared<Grandma>();

    addGenerator(autoclicker);
    addGenerator(grandma);

    // Add Upgrades
    addUpgrade(std::make_shared<AutoclickerUpgrade>(autoclicker));
    addUpgrade(std::make_shared<GoldenDoughUpgrade>(generators));
}

void GameManager::addGenerator(std::shared_ptr<ClickableItem> generator) {
    generators.push_back(generator);
}

void GameManager::addUpgrade(std::shared_ptr<Upgrade> upgrade) {
    upgrades.push_back(upgrade);
}

void GameManager::run() {
    using clock = std::chrono::steady_clock;
    auto lastUpdate = clock::now();

    while (running) {
        auto now = clock::now();
        std::chrono::duration<double> elapsed = now - lastUpdate;
        lastUpdate = now;

        updateGenerators(elapsed.count());

        displayMenu();

        int choice;
        std::cin >> choice;
        handleInput(choice);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}




void GameManager::updateGenerators(double deltaTime) {
    double cookiesGenerated = 0.0;
    for (const auto& generator : generators) {
        cookiesGenerated += generator->getCookiesPerSecond() * deltaTime;
    }

    totalCookies += cookiesGenerated;
    stats.addCookies(cookiesGenerated);
    stats.setCPS(cookiesGenerated); // Just for display, overwrite each frame
}

void GameManager::displayMenu() {
    std::cout << "\n=== COOKIE EMPIRE ===\n";
    std::cout << "Cookies: " << (int)totalCookies << "\n";
    std::cout << "CPS: " << stats.getCPS() << "\n";
    std::cout << "1. Manual Click (+1 cookie)\n";
    std::cout << "2. Buy Generators\n";
    std::cout << "3. Buy Upgrades\n";
    std::cout << "4. Exit\n";
    std::cout << "Select: ";
}

void GameManager::handleInput(int choice) {
    switch (choice) {
        case 1:
            totalCookies += 1;
            stats.addCookies(1);
            stats.addClick();
            break;

        case 2: {
            std::cout << "\nAvailable Generators:\n";
            for (size_t i = 0; i < generators.size(); ++i) {
                std::cout << i + 1 << ". " << generators[i]->getName()
                          << " (Qty: " << generators[i]->getQuantity()
                          << ", Price: " << generators[i]->getPrice() << ")\n";
            }

            std::cout << "Select generator: ";
            int genChoice;
            std::cin >> genChoice;

            if (genChoice >= 1 && genChoice <= (int)generators.size()) {
                auto& gen = generators[genChoice - 1];
                if (totalCookies >= gen->getPrice()) {
                    totalCookies -= gen->getPrice();
                    gen->purchase();
                } else {
                    std::cout << "Not enough cookies!\n";
                }
            }
            break;
        }

        case 3:
            purchaseUpgradeMenu();
            break;

        case 4:
            running = false;
            break;

        default:
            std::cout << "Invalid input.\n";
    }
}

void GameManager::purchaseUpgradeMenu() {
    std::cout << "\nAvailable Upgrades:\n";
    for (size_t i = 0; i < upgrades.size(); ++i) {
        std::string status = upgrades[i]->isPurchased() ? " [Purchased]" : "";
        std::cout << i + 1 << ". " << upgrades[i]->getName()
                  << " - " << upgrades[i]->getPrice() << status << "\n";
    }

    std::cout << "Select upgrade: ";
    int choice;
    std::cin >> choice;

    if (choice >= 1 && choice <= (int)upgrades.size()) {
        auto& upgrade = upgrades[choice - 1];
        if (!upgrade->isPurchased()) {
            if (totalCookies >= upgrade->getPrice()) {
                totalCookies -= upgrade->getPrice();
                upgrade->applyUpgrade();
                upgrade->purchaseUpgrade();
                stats.addUpgrade();
                std::cout << "Upgrade applied!\n";
            } else {
                std::cout << "Not enough cookies!\n";
            }
        } else {
            std::cout << "Already purchased.\n";
        }
    }
}
