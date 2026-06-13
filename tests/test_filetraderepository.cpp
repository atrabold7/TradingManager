#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "FileTradeRepository.h"
#include "Trade.h"

// ---------------------------------------------------------------------
// TEST BLOCK 1: checking functions working properly
// ---------------------------------------------------------------------
TEST_CASE("FileTraderRepository - check functions", "[FileTraderRepository]") {
    // create vars
    std::string name = "Apple";
    float amount = 10.0f;
    float buyPrice = 150.50f;
    float tax = 25.0f;
    float buyFee = 4.90f;
    std::chrono::year_month_day buyDate{std::chrono::year(2026), std::chrono::month(6), std::chrono::day(2)};
    
    // create trades
    std::vector<Trade> readTrades;
    std::vector<Trade> writeTrades;
    
    writeTrades.emplace_back(name, amount, buyPrice, buyFee, buyDate);
    writeTrades.emplace_back(name, amount, buyPrice, buyFee, buyDate);
    writeTrades.emplace_back(name, amount, buyPrice, buyFee, buyDate);
    
    auto repo = std::make_unique<FileTradeRepository>();
    
    REQUIRE(repo->saveData(writeTrades, "test_file.json"));
    REQUIRE(repo->readTrades(readTrades, "test_file.json"));
    REQUIRE(writeTrades == readTrades);
    
    std::remove("test_file.json");
}
