#include <SFML\Graphics.hpp>
#include "GameManager.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <algorithm>

struct FloatingText {
    sf::Text text;
    sf::Vector2f velocity;
    float lifetime;
};

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 500}, 32), "I Eat Cookies");

    sf::Font font;
    if (!font.openFromFile("../assets/arial.ttf")) {
        std::cerr << "no fonts detected\n";
        return 1;
    }

    sf::Texture cookiePixelTex, cookieSmoothTex, cookieBlurTex, cookieGoldenTex;
    if (!cookiePixelTex.loadFromFile("../assets/cookie_pixel.png")) std::cerr << "Failed to load cookie_pixel.png\n";
    if (!cookieSmoothTex.loadFromFile("../assets/cookie_smooth.png")) std::cerr << "Failed to load cookie_smooth.png\n";
    if (!cookieBlurTex.loadFromFile("../assets/cookie_broken.png")) std::cerr << "Failed to load cookie_blur.png\n";
    if (!cookieGoldenTex.loadFromFile("../assets/cookie_golden.png")) std::cerr << "Failed to load cookie_golden.png\n";

    sf::CircleShape cookieShape(100.f);
    cookieShape.setOrigin(sf::Vector2f(100.f, 100.f));
    cookieShape.setFillColor(sf::Color(139, 69, 19));
    cookieShape.setPosition(sf::Vector2f(720.f / 2.f, 480.f / 2.f));

    sf::Sprite cookieSprite(cookiePixelTex);
    cookieSprite.setOrigin(sf::Vector2f(100.f, 100.f));
    cookieSprite.setPosition(sf::Vector2f(720.f / 2.f, 480.f / 2.f));

    bool usingShape = true;

    GameManager game;
    sf::Clock cpsClock;
    sf::Clock autosaveClock;
    sf::Clock animationClock;

    float cookieScale = 1.f;
    bool cookieClicked = false;

    std::vector<FloatingText> floatingTexts;

    sf::Text cookieText(font, "Cookies: 0", 30);
    cookieText.setFillColor(sf::Color::White);
    cookieText.setPosition({20.f, 20.f});

    sf::Text totalCps(font, "CPS: 0", 20);
    totalCps.setFillColor(sf::Color::Yellow);
    totalCps.setPosition({20.f, 60.f});

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

    while (window.isOpen()) {
        float deltaTime = animationClock.restart().asSeconds();

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (auto e = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (e->button == sf::Mouse::Button::Left) {
                    float mouseX = static_cast<float>(e->position.x);
                    float mouseY = static_cast<float>(e->position.y);
                    sf::Vector2f mouse(mouseX, mouseY);

                    if ((usingShape && cookieShape.getGlobalBounds().contains(mouse)) ||
                        (!usingShape && cookieSprite.getGlobalBounds().contains(mouse))) {
                        game.handleChoice(1);
                        cookieClicked = true;
                        cookieScale = 1.2f;

                        sf::Text plus(font, "+1", 20);
                        plus.setFillColor(sf::Color::White);
                        plus.setPosition(mouse);
                        floatingTexts.push_back({plus, sf::Vector2f(0, -40.f), 1.0f});
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

        if (cookieClicked) {
            cookieScale -= deltaTime * 1.5f;
            if (cookieScale <= 1.f) {
                cookieScale = 1.f;
                cookieClicked = false;
            }
            if (usingShape) {
                cookieShape.setScale(sf::Vector2f(cookieScale, cookieScale));
            } else {
                cookieSprite.setScale(sf::Vector2f(cookieScale, cookieScale));
            }
        }

        for (auto& text : floatingTexts) {
            text.text.move(text.velocity * deltaTime);
            text.lifetime -= deltaTime;
            sf::Color color = text.text.getFillColor();
            color.a = static_cast<uint8_t>(255 * (text.lifetime));
            text.text.setFillColor(color);
        }
        floatingTexts.erase(
            std::remove_if(floatingTexts.begin(), floatingTexts.end(), [](const FloatingText& t) {
                return t.lifetime <= 0;
            }),
            floatingTexts.end()
        );

        float cps = game.calculateTotalCps();

        if (cps >= 5.f) {
            cookieSprite.setTexture(cookieGoldenTex);
            usingShape = false;
        } else if (cps >= 4.f) {
            cookieSprite.setTexture(cookieBlurTex);
            usingShape = false;
        } else if (cps >= 3.f) {
            cookieSprite.setTexture(cookieSmoothTex);
            usingShape = false;
        } else if (cps >= 2.f) {
            cookieSprite.setTexture(cookiePixelTex);
            usingShape = false;
        } else {
            usingShape = true;
        }

        cookieText.setString("Cookies: " + std::to_string(game.getCookieCount()));

        std::ostringstream cpsStream;
        cpsStream.precision(2);
        cpsStream << std::fixed << "CPS: " << cps;
        totalCps.setString(cpsStream.str());

        factoryInfo.setString("Cost: " + std::to_string(game.getGeneratorCost(0)) +
                               " | Lvl: " + std::to_string(game.getGeneratorLevel(0)));
        grandmaInfo.setString("Cost: " + std::to_string(game.getGeneratorCost(1)) +
                               " | Lvl: " + std::to_string(game.getGeneratorLevel(1)));
        autoclickerInfo.setString("Cost: " + std::to_string(game.getGeneratorCost(2)) +
                                  " | Lvl: " + std::to_string(game.getGeneratorLevel(2)));

        window.clear();
        if (usingShape) window.draw(cookieShape);
        else window.draw(cookieSprite);
        window.draw(cookieText);
        window.draw(totalCps);
        window.draw(buyFactory);
        window.draw(factoryInfo);
        window.draw(buyGrandma);
        window.draw(grandmaInfo);
        window.draw(buyAutoclicker);
        window.draw(autoclickerInfo);

        for (auto& t : floatingTexts) {
            window.draw(t.text);
        }

        window.display();
    }

    return 0;
}
