#include <catch2/catch_test_macros.hpp>
#include "Trade.h"

// ---------------------------------------------------------------------
// TEST BLOCK 1: Überprüfung des Konstruktors und der Standardwerte
// ---------------------------------------------------------------------
TEST_CASE("Trade - Konstruktor und Getter testen", "[Trade]") {
    // 1. Spieldaten vorbereiten (Setup)
    std::string name = "Apple";
    float amount = 10.0f;
    float buyPrice = 150.50f;
    float tax = 25.0f;
    float buyFee = 4.90f;
    
    // Datum definieren mit der C++20 Syntax (wichtig wegen deiner Trade.h)
    std::chrono::year_month_day buyDate{std::chrono::year(2026), std::chrono::month(6), std::chrono::day(2)};

    // 2. Objekt erstellen (Execution)
    Trade testTrade(name, amount, buyPrice, tax, buyFee, buyDate);

    // 3. Prüfen, ob die Daten korrekt im Objekt gespeichert wurden (Assertion)
    // REQUIRE bricht den Test sofort ab, wenn die Bedingung nicht stimmt
    REQUIRE(testTrade.getStockName() == "Apple");
    REQUIRE(testTrade.getStockAmount() == 10.0f);
    REQUIRE(testTrade.getSingleBuyPrice() == 150.50f);
    REQUIRE(testTrade.getTax() == 25.0f);
    REQUIRE(testTrade.getBuyFee() == 4.90f);
    REQUIRE(testTrade.getBuyDate() == buyDate);

    // WICHTIG: Wir prüfen auch die Standardwerte, die im Konstruktor nicht übergeben wurden!
    // Ein neu erstellter Trade darf standardmäßig noch nicht geschlossen sein.
    REQUIRE(testTrade.getTradeClosed() == false);
    REQUIRE(testTrade.getSellDate().has_value() == false);
}

// ---------------------------------------------------------------------
// TEST BLOCK 2: Überprüfung der Setter-Funktionen
// ---------------------------------------------------------------------
TEST_CASE("Trade - Setter veraendern den Zustand korrekt", "[Trade]") {
    // Wir starten mit einem leeren Trade über den Default-Konstruktor
    Trade testTrade; 

    // Wir simulieren den Verkauf der Aktie über deine Setter-Funktionen
    testTrade.setTradeClosed(true);
    testTrade.setSingleSellPrice(180.0f);
    testTrade.setSellFee(5.0f);

    // Jetzt prüfen wir, ob die Setter die privaten Variablen wirklich verändert haben
    REQUIRE(testTrade.getTradeClosed() == true);
    REQUIRE(testTrade.getSingleSellPrice() == 180.0f);
    REQUIRE(testTrade.getSellFee() == 5.0f);
}