#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "FileTradeRepository.h"
#include "Trade.h"
#include "TradingConstants.h"

// ---------------------------------------------------------------------
// TEST BLOCK 1: checking functions working properly
// ---------------------------------------------------------------------
TEST_CASE("FileTraderRepository - check functions", "[FileTraderRepository]") {
    // create vars
    std::string name = "Apple";
    long long amount = 900000000;
    long long buyPrice = 33560000000;
    long long buyFee = 955000000;
    std::chrono::year_month_day buyDate{std::chrono::year(2026), std::chrono::month(6), std::chrono::day(2)};
    
    // create trades
    std::vector<Trade> readTrades;
    std::vector<Trade> writeTrades;
    
    writeTrades.emplace_back(name, amount, buyPrice, buyFee, buyDate);
    writeTrades.emplace_back(name, amount, buyPrice, buyFee, buyDate);
    writeTrades.emplace_back(name, amount, buyPrice, buyFee, buyDate);
    
    auto repo = std::make_unique<FileTradeRepository>(std::string(Trading::FILESTOCKSTEST));
    
    REQUIRE(repo->saveData(writeTrades));
    REQUIRE(repo->readTrades(readTrades));
    REQUIRE(writeTrades == readTrades);
    
    std::remove(Trading::FILESTOCKSTEST.data());
}
