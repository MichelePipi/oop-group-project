#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include <iostream>
#include <sstream>

int main() {
    sf::RenderWindow window(sf::VideoMode({720, 480}, 32), "I Eat Cookies");

    sf::Font font;
    if (!font.openFromFile("../assets/arial.ttf")) {
        std::cerr << "no fonts found\n";
        return 1;
    }

    sf::Text cookieText(font, "Cookies: 0", 30);
    cookieText.setFillColor(sf::Color::White);
    cookieText.setPosition({20.f, 20.f});

    sf::CircleShape cookie(100.f);
    cookie.setFillColor(sf::Color(139, 69, 19));
    cookie.setPosition({300.f, 200.f});

    GameManager game;
    sf::Clock cpsClock;
    sf::Clock autosaveClock;

    //buttons, labelings
    sf::Text buyFactory(font, "Buy Factory", 20);
    buyFactory.setPosition({50.f, 400.f});
    buyFactory.setFillColor(sf::Color::Green);

    sf::Text factoryInfo(font, "", 16);
    factoryInfo.setPosition({50.f, 430.f});

    sf::Text buyGrandma(font, "Buy Grandma", 20);
    buyGrandma.setPosition({300.f, 400.f});
    buyGrandma.setFillColor(sf::Color::Cyan);

    sf::Text grandmaInfo(font, "", 16);
    grandmaInfo.setPosition({300.f, 430.f});

    sf::Text buyAutoclicker(font, "Buy Autoclicker", 20);
    buyAutoclicker.setPosition({550.f, 400.f});
    buyAutoclicker.setFillColor(sf::Color::Yellow);

    sf::Text autoclickerInfo(font, "", 16);
    autoclickerInfo.setPosition({550.f, 430.f});

    sf::Text totalCps(font, "CPS: 0", 20);
    totalCps.setFillColor(sf::Color::White);
    totalCps.setPosition({20.f, 60.f});

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (auto e = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (e->button == sf::Mouse::Button::Left) {
                    float mouseX = static_cast<float>(e->position.x);
                    float mouseY = static_cast<float>(e->position.y);
                    sf::Vector2f mouse(mouseX, mouseY);

                    if (cookie.getGlobalBounds().contains(mouse)) {
                        game.handleChoice(1);
                    } else if (buyFactory.getGlobalBounds().contains(mouse)) {
                        game.handleChoice(2);
                    } else if (buyGrandma.getGlobalBounds().contains(mouse)) {
                        game.handleChoice(3);
                    } else if (buyAutoclicker.getGlobalBounds().contains(mouse)) {
                        game.handleChoice(4);
                    }
                }
            }
        }

        if (cpsClock.getElapsedTime().asSeconds() >= 1.f) {
            game.runAutoGeneration();
            cpsClock.restart();
        }

        if (autosaveClock.getElapsedTime().asSeconds() >= 30.f) {
            game.saveGame();
            autosaveClock.restart();
        }

        cookieText.setString("Cookies: " + std::to_string(game.getCookieCount()));

        std::ostringstream cpsStream;
        cpsStream.precision(2);
        cpsStream << std::fixed << "CPS: " << game.calculateTotalCps();
        totalCps.setString(cpsStream.str());

        factoryInfo.setString("Cost: " + std::to_string(game.getGeneratorCost(0)) +
                               " | Lvl: " + std::to_string(game.getGeneratorLevel(0)));
        grandmaInfo.setString("Cost: " + std::to_string(game.getGeneratorCost(1)) +
                               " | Lvl: " + std::to_string(game.getGeneratorLevel(1)));
        autoclickerInfo.setString("Cost: " + std::to_string(game.getGeneratorCost(2)) +
                                  " | Lvl: " + std::to_string(game.getGeneratorLevel(2)));

        window.clear();
        window.draw(cookie);
        window.draw(cookieText);
        window.draw(totalCps);
        window.draw(buyFactory);
        window.draw(factoryInfo);
        window.draw(buyGrandma);
        window.draw(grandmaInfo);
        window.draw(buyAutoclicker);
        window.draw(autoclickerInfo);
        window.display();
    }

    return 0;
}