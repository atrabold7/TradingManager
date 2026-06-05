#include <fstream>
#include <catch2/catch_test_macros.hpp>
#include "Trade.h"
#include "TradeSerializer.h"

// ---------------------------------------------------------------------
// TEST BLOCK 1: Überprüfung des Konstruktors und der Standardwerte
// ---------------------------------------------------------------------
TEST_CASE("TradeSerializer - Gewinnberechnung", "[TradeSerializer]") {
    // 1. Spieldaten vorbereiten (Setup)
    std::string StockName {"Alphabet"};
    float StockAmount = 10.0f;
    float SingleBuyPrice = 300.0f;
    float Tax = 40.0f;
    float BuyFee = 20.0f;
    std::chrono::year_month_day BuyDate {std::chrono::year(2026), std::chrono::month(6), std::chrono::day(2)};;
    std::optional<std::chrono::year_month_day> SellDate;
    float SingleSellPrice = 0.0f;
    float SellFee = 0.0f;
    int HoldingPeriod = 0;
    bool TradeClosed = false;
    
    // 2. Objekt erstellen (Execution)
    std::vector<Trade> tradesToWrite;
    std::vector<Trade> tradesToLoad;
    tradesToWrite.emplace_back(StockName, StockAmount, SingleBuyPrice, Tax, BuyFee, BuyDate);
    std::stringstream ss;
    
    // 3. Datein in json Datei schreiben und auslesen
    TradeSerializer::saveData(ss, tradesToWrite);
    ss.seekg(0);
    TradeSerializer::readTrades(ss, tradesToLoad);    
    
    // 4. Prüfen, ob richtig in json geschrieben und ausgelesen wird
    // REQUIRE bricht den Test sofort ab, Daten beim Schreiben und Auslesen nicht identisch sind
    SECTION("Data must be the same")
    {
        REQUIRE(StockName == tradesToLoad[0].getStockName());
    }
}