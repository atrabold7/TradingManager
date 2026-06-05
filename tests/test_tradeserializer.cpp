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
    std::chrono::year_month_day BuyDate {std::chrono::year(2026), std::chrono::month(6), std::chrono::day(2)};
    float SingleSellPrice = 350.0f;
    float SellFee = 30.0f;
    int HoldingPeriod = 8;
    bool TradeClosed = false;
    
    std::optional<std::chrono::year_month_day> SellDate = 
        std::chrono::year_month_day{std::chrono::year(2026), std::chrono::month(6), std::chrono::day(10)};
        
    // 2. Objekt erstellen (Execution)
    std::vector<Trade> tradesToWrite;
    std::vector<Trade> tradesToLoad;
    
    tradesToWrite.emplace_back(StockName, StockAmount, SingleBuyPrice, Tax, BuyFee, BuyDate);
    tradesToWrite[0].setSellDate(SellDate.value());
    tradesToWrite[0].setSingleSellPrice(SingleSellPrice);
    tradesToWrite[0].setSellFee(SellFee);
    tradesToWrite[0].setHoldingPeriod(HoldingPeriod);
    tradesToWrite[0].setTradeClosed(false);
    
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
        REQUIRE(StockAmount == tradesToLoad[0].getStockAmount());
        REQUIRE(SingleBuyPrice == tradesToLoad[0].getSingleBuyPrice());
        REQUIRE(Tax == tradesToLoad[0].getTax());
        REQUIRE(BuyFee == tradesToLoad[0].getBuyFee());
        
        REQUIRE(BuyDate.year() == tradesToLoad[0].getBuyDate().year());
        REQUIRE(BuyDate.month() == tradesToLoad[0].getBuyDate().month());
        REQUIRE(BuyDate.day() == tradesToLoad[0].getBuyDate().day());
        
        REQUIRE(SellDate.value().year() == tradesToLoad[0].getSellDate().value().year());
        REQUIRE(SellDate.value().month() == tradesToLoad[0].getSellDate().value().month());
        REQUIRE(SellDate.value().day() == tradesToLoad[0].getSellDate().value().day());
        
        REQUIRE(SingleSellPrice == tradesToLoad[0].getSingleSellPrice());
        REQUIRE(SellFee == tradesToLoad[0].getSellFee());
        REQUIRE(HoldingPeriod == tradesToLoad[0].getHoldingPeriod());
        REQUIRE(TradeClosed == tradesToLoad[0].getTradeClosed());
    }
}