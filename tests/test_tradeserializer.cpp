#include <fstream>
#include <catch2/catch_test_macros.hpp>
#include "Trade.h"
#include "TradeSerializer.h"

// ---------------------------------------------------------------------
// TEST BLOCK 1: checking constructor and values
// ---------------------------------------------------------------------
TEST_CASE("TradeSerializer - json Test", "[TradeSerializer]") {
    // fill vars
    std::string StockName[3] {"Alphabet", "BYD", "Rheinmetall"};
    long long StockAmount = 9900000000;
    long long SingleBuyPrice = 6176000000;
    long long Tax = 5560000000;
    long long BuyFee = 2245000000;
    std::chrono::year_month_day BuyDate {std::chrono::year(2026), std::chrono::month(6), std::chrono::day(2)};
    long long SingleSellPrice = 6380000000;
    long long SellFee = 1956000000;
    
    std::optional<std::chrono::year_month_day> SellDate = 
        std::chrono::year_month_day{std::chrono::year(2026), std::chrono::month(6), std::chrono::day(10)};
        
    // create objects
    std::vector<Trade> tradesToWrite;
    std::vector<Trade> tradesToLoad;
    
    // Check with empty vector
    // REQUIRE no crash with no data
    SECTION("No entry check")
    {
        std::stringstream ss;
        
        TradeSerializer::saveData(ss, tradesToWrite);
        ss.seekg(0);
        TradeSerializer::readTrades(ss, tradesToLoad);
        
        REQUIRE(tradesToLoad.empty());
        REQUIRE(tradesToLoad.size() == 0);
    }
    
    // Check for one entry
    // REQUIRE crash if both entries are not equal
    SECTION("Data must be the same")
    {
        tradesToWrite.emplace_back(StockName[0], StockAmount, SingleBuyPrice, BuyFee, BuyDate);
        tradesToWrite[0].setSellDate(SellDate.value());
        tradesToWrite[0].setSingleSellPrice(SingleSellPrice);
        tradesToWrite[0].setSellFee(SellFee);
        tradesToWrite[0].setTax(Tax);
        tradesToWrite[0].setTradeClosed(true);
        
        std::stringstream ss;
    
        // write data in json file and read it
        TradeSerializer::saveData(ss, tradesToWrite);
        ss.seekg(0);
        TradeSerializer::readTrades(ss, tradesToLoad);
        
        REQUIRE(tradesToWrite[0] == tradesToLoad[0]);
    }
    
    // Check with more entries
    // REQUIRE crash if all entries are not equal
    SECTION("Data must be the same")
    {
        for (int ii = 0; ii < 3; ++ii)
        {
            tradesToWrite.emplace_back(StockName[ii], StockAmount, SingleBuyPrice, BuyFee, BuyDate);
            tradesToWrite[ii].setSellDate(SellDate.value());
            tradesToWrite[ii].setSingleSellPrice(SingleSellPrice);
            tradesToWrite[ii].setSellFee(SellFee);
            tradesToWrite[0].setTax(Tax);
            tradesToWrite[ii].setTradeClosed(true);
        }
        std::stringstream ss;
    
        // write data in json file and read it
        TradeSerializer::saveData(ss, tradesToWrite);
        ss.seekg(0);
        TradeSerializer::readTrades(ss, tradesToLoad);
        
        int counter{0};
        for (const Trade &tradeToWrite: tradesToWrite)
        {
            REQUIRE(tradeToWrite == tradesToLoad[counter]);
            counter++;
        }
    }
}