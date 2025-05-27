#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "All.hpp"
#include <math.h>
// #include "../src/*"

TEST_CASE("GameManager initializes correctly") {
    GameManager gm;
    CHECK(gm.getCookieCount() == 0);
    CHECK(gm.calculateTotalCps() == 0.0f);
}

TEST_CASE("3 factories, 2 autoclickers, 1 grandma") {
    GameManager gm;
    gm.setCookies(9999999);
    gm.handleChoice(2);
    gm.handleChoice(2);
    gm.handleChoice(2);
    gm.handleChoice(3);
    gm.handleChoice(4);
    gm.handleChoice(4); // factory = 2, grandma = 3, autoclicker = 4

    CHECK(gm.calculateTotalCps()==1.95f);
}

// come up with more tests

TEST_CASE("50 factories, 999 autoclickers, 2 grandma") {
    GameManager gm;
    long long c = 9223372036854775807LL;
    gm.setCookies(c);
    for (int i = 0; i < 50; i++) {
        gm.handleChoice(2);
    }
    for (int i = 0; i < 999; i++) {
        gm.handleChoice(4);
    }
    for (int i = 0; i < 2; i++) {
        gm.handleChoice(3);
    }
    CHECK(gm.calculateTotalCps() == doctest::Approx(75.65));
}

TEST_CASE("price of autoclicker at level 50") {
    // return static_cast<int>(baseCost * pow(1.10f, level));
    GameManager gm;
    long long c = 9223372036854775807LL;
    gm.setCookies(c);
    for (int i = 0; i < 49; i++) {
        gm.handleChoice(4);
    }
    CHECK(gm.generators[2]->getCost() == 533);
}

// test garble save file
TEST_CASE("Test garblefile.txt") {
    GameManager gm;
    gm.saveFile.loadFile();

    CHECK(gm.calculateTotalCps() == 0.f);
}

TEST_CASE("Test random save data [valid]") {
    GameManager gm;
    gm.loadSaveData(gm.saveFile.loadFile());

    CHECK(gm.getCookieCount() == 1026628LL);
}

