#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <memory>

#include "Action.hpp"
#include "../include/portable-file-dialogs.h"

// Enum to manage the current game state
enum class GameState { MainMenu, Playing };

// Struct for animated floating "+1" texts
struct FloatingText {
    sf::Text text;
    sf::Vector2f velocity;
    float lifetime;
};

int main() {
    bool showSavedMessage = false; // Flag to determine whether to show "Game saved!"

    // Create game window
    sf::RenderWindow window(sf::VideoMode({800, 500}, 32), "I Eat Cookies");

    // Load font
    sf::Font font;
    if (!font.openFromFile("./assets/arial.ttf")) {
        std::cerr << "no fonts detected\n";
        return 1;
    }

    GameState gameState = GameState::MainMenu;

    // ---------- Main Menu Texts ----------
    sf::Text title(font, "I Eat Cookies", 50);
    title.setFillColor(sf::Color::White);
    title.setPosition({200.f, 50.f});

    sf::Text startBtn(font, "START", 30);
    startBtn.setFillColor(sf::Color::Green);
    startBtn.setPosition({320.f, 150.f});

    sf::Text loadBtn(font, "LOAD", 30);
    loadBtn.setFillColor(sf::Color::Yellow);
    loadBtn.setPosition({320.f, 210.f});

    sf::Text backToMainMenu(font, "MAIN MENU", 20);
    backToMainMenu.setFillColor(sf::Color::Green);
    backToMainMenu.setPosition({600.f, 20.f});

    sf::Text guide(font, "Factories provide 0.5 CPS.\nGrandmas provide 0.35 CPS.\nAutoclickers provide 0.05 CPS.", 40);
    guide.setFillColor(sf::Color::White);
    guide.setPosition({120.f, 300.f});

    // ---------- Load Cookie Textures ----------
    sf::Texture cookiePixelTex, cookieSmoothTex, cookieBlurTex, cookieGoldenTex;
    cookiePixelTex.loadFromFile("./assets/cookie_pixel.png");
    cookieSmoothTex.loadFromFile("./assets/cookie_smooth.png");
    cookieBlurTex.loadFromFile("./assets/cookie_broken.png");
    cookieGoldenTex.loadFromFile("./assets/cookie_golden.png");

    // ---------- Cookie Visual ----------
    sf::CircleShape cookieShape(100.f);
    cookieShape.setOrigin(100.f, 100.f);
    cookieShape.setFillColor(sf::Color(139, 69, 19));
    cookieShape.setPosition(360.f, 240.f);

    sf::Sprite cookieSprite(cookiePixelTex);
    cookieSprite.setOrigin(100.f, 100.f);
    cookieSprite.setPosition(360.f, 240.f);

    bool usingShape = true; // Whether to use the shape or the sprite
    std::unique_ptr<GameManager> game = std::make_unique<GameManager>();
    sf::Clock cpsClock, animationClock;

    float cookieScale = 1.f;
    bool cookieClicked = false;
    std::vector<FloatingText> floatingTexts;

    // ---------- UI Text ----------
    sf::Text cookieText(font, "Cookies: 0", 30);
    cookieText.setPosition({20.f, 20.f});
    cookieText.setFillColor(sf::Color::White);

    sf::Text saveText(font, "SAVE", 30);
    saveText.setPosition({320.f, 20.f});
    saveText.setFillColor(sf::Color::White);

    sf::Text totalCps(font, "CPS: 0", 20);
    totalCps.setPosition({20.f, 60.f});
    totalCps.setFillColor(sf::Color::Yellow);

    // ---------- Generator Buttons ----------
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

    // ---------- Golden Cookie Dough ----------
    sf::Text goldenCookieDough(font, "Buy Golden Cookie Dough", 20);
    goldenCookieDough.setPosition({550.f, 250.f});
    goldenCookieDough.setFillColor(sf::Color::Green);
    sf::Text goldenCookieDoughInfo(font, "\n x2 CPS Permanently.", 16);
    goldenCookieDoughInfo.setPosition({550.f, 270.f});
    goldenCookieDoughInfo.setFillColor(sf::Color::White);

    // ---------- Save Confirmation ----------
    sf::Text savedMessage(font, "", 20);
    savedMessage.setPosition({300.f, 60.f});
    sf::Clock savedMessageClock;

    // ---------- Error Message for Save Loading ----------
    sf::Text errorText(font, "Failed to load save data!", 24);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition({100.f, 100.f});
    sf::Clock errorClock;
    bool showError = false;

    // Main Game Loop
    while (window.isOpen()) {
        float deltaTime = animationClock.restart().asSeconds();

        // Handle events
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            // Handle mouse clicks
            if (auto e = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (e->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mouse(static_cast<float>(e->position.x), static_cast<float>(e->position.y));

                    if (gameState == GameState::MainMenu) {
                        if (startBtn.getGlobalBounds().contains(mouse)) {
                            gameState = GameState::Playing;
                        } else if (loadBtn.getGlobalBounds().contains(mouse)) {
                            std::vector<double> variables = game->saveFile.loadFile();
                            if (variables.empty()) {
                                showError = true;
                                errorClock.restart();
                            } else {
                                game->setCookies((long)variables[0]);
                                game->generators[0]->setLevel((int)variables[1]);
                                game->generators[1]->setLevel((int)variables[2]);
                                game->generators[2]->setLevel((int)variables[3]);
                                game->hasGoldenDough = (bool)variables[4];
                            }
                        }
                    } else if (gameState == GameState::Playing) {
                        // Cookie clicked
                        if ((usingShape && cookieShape.getGlobalBounds().contains(mouse)) ||
                            (!usingShape && cookieSprite.getGlobalBounds().contains(mouse))) {
                            game->handleChoice(1);
                            cookieClicked = true;
                            cookieScale = 1.2f;
                            sf::Text plus(font, "+1", 20);
                            plus.setFillColor(sf::Color::White);
                            plus.setPosition(mouse);
                            floatingTexts.push_back({plus, sf::Vector2f(0, -40.f), 1.0f});

                        } else if (buyFactory.getGlobalBounds().contains(mouse)) {
                            game->handleChoice(BUY_FACTORY);
                        } else if (buyGrandma.getGlobalBounds().contains(mouse)) {
                            game->handleChoice(BUY_GRANDMA);
                        } else if (buyAutoclicker.getGlobalBounds().contains(mouse)) {
                            game->handleChoice(BUY_AUTOCLICKER);
                        } else if (saveText.getGlobalBounds().contains(mouse)) {
                            game->handleChoice(SAVE_FILE);
                            std::string uuid = game->saveFile.generateFileName();
                            savedMessage.setString("Saved to [" + uuid.substr(0, 5) + "]");
                            savedMessageClock.restart();
                            showSavedMessage = true;
                        } else if (backToMainMenu.getGlobalBounds().contains(mouse)) {
                            gameState = GameState::MainMenu;
                        } else if (goldenCookieDough.getGlobalBounds().contains(mouse)) {
                            game->handleChoice(BUY_GOLDEN_DOUGH);
                        }
                    }
                }
            }
        }

        // Auto Cookie Generation & Animation Updates
        if (gameState == GameState::Playing) {
            if (cpsClock.getElapsedTime().asSeconds() >= 1.f) {
                game->runAutoGeneration();
                game->setCookies(game->getCookieCount() + game->calculateTotalCps());
                cpsClock.restart();
            }

            // Cookie click animation
            if (cookieClicked) {
                cookieScale -= deltaTime * 1.5f;
                if (cookieScale <= 1.f) {
                    cookieScale = 1.f;
                    cookieClicked = false;
                }
                if (usingShape) cookieShape.setScale({cookieScale, cookieScale});
                else cookieSprite.setScale({cookieScale, cookieScale});
            }

            // Update floating "+1" animations
            for (auto& text : floatingTexts) {
                text.text.move(text.velocity * deltaTime);
                text.lifetime -= deltaTime;
                sf::Color color = text.text.getFillColor();
                color.a = static_cast<uint8_t>(255 * (text.lifetime));
                text.text.setFillColor(color);
            }
            floatingTexts.erase(std::remove_if(floatingTexts.begin(), floatingTexts.end(), [](const FloatingText& t) {
                return t.lifetime <= 0;
            }), floatingTexts.end());

            // Cookie style based on CPS
            float cps = game->calculateTotalCps();
            if (cps >= 5.f)      { cookieSprite.setTexture(cookieGoldenTex); usingShape = false; }
            else if (cps >= 4.f) { cookieSprite.setTexture(cookieBlurTex);   usingShape = false; }
            else if (cps >= 3.f) { cookieSprite.setTexture(cookieSmoothTex); usingShape = false; }
            else if (cps >= 2.f) { cookieSprite.setTexture(cookiePixelTex);  usingShape = false; }
            else                 { usingShape = true; }

            // Golden Cookie Dough Info
            goldenCookieDoughInfo.setString("Cost: 500, Active: " + std::string(game->hasGoldenDough ? "YES" : "NO") + "\n x2 CPS Permanently.");

            // Update display text
            cookieText.setString("Cookies: " + std::to_string(game->getCookieCount()));
            std::ostringstream cpsStream;
            cpsStream.precision(2);
            cpsStream << std::fixed << "CPS: " << cps;
            totalCps.setString(cpsStream.str());
            factoryInfo.setString("Cost: " + std::to_string(game->getGeneratorCost(0)) + " | Lvl: " + std::to_string(game->getGeneratorLevel(0)));
            grandmaInfo.setString("Cost: " + std::to_string(game->getGeneratorCost(1)) + " | Lvl: " + std::to_string(game->getGeneratorLevel(1)));
            autoclickerInfo.setString("Cost: " + std::to_string(game->getGeneratorCost(2)) + " | Lvl: " + std::to_string(game->getGeneratorLevel(2)));
        }

        // ---------- RENDER ----------
        window.clear();

        if (gameState == GameState::MainMenu) {
            window.draw(title);
            window.draw(startBtn);
            window.draw(loadBtn);
            window.draw(guide);
            if (showError && errorClock.getElapsedTime().asSeconds() < 5.0f) {
                window.draw(errorText);
            } else {
                showError = false;
            }
        } else if (gameState == GameState::Playing) {
            if (usingShape) window.draw(cookieShape);
            else window.draw(cookieSprite);

            window.draw(cookieText);
            window.draw(totalCps);
            window.draw(buyFactory);      window.draw(factoryInfo);
            window.draw(buyGrandma);      window.draw(grandmaInfo);
            window.draw(buyAutoclicker);  window.draw(autoclickerInfo);
            window.draw(saveText);
            window.draw(backToMainMenu);
            window.draw(goldenCookieDough);
            window.draw(goldenCookieDoughInfo);

            for (auto& t : floatingTexts) window.draw(t.text);
            if (showSavedMessage && savedMessageClock.getElapsedTime().asSeconds() < 3.f)
                window.draw(savedMessage);
        }
        window.display();
    }
    return 0;
}
