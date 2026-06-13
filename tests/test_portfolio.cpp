#include <TradeInputHandler.h>
#include <catch2/catch_test_macros.hpp>
#include "Portfolio.h"
#include "Trade.h"

// ---------------------------------------------------------------------
// TEST BLOCK 1: Überprüfung des Konstruktors und der Standardwerte
// ---------------------------------------------------------------------
TEST_CASE("Portfolio - Gewinnberechnung", "[Portfolio]") {
    // 1. Spieldaten vorbereiten (Setup)
    TradeInputData tradeInputData;
    tradeInputData.m_StockName = "Alphabet";
    tradeInputData.m_StockAmount = 10;
    tradeInputData.m_SingleBuyPrice = 300;
    tradeInputData.m_BuyFee = 10;
    tradeInputData.m_BuyDate = std::chrono::year(2026) / 6 / 2;
    
    // 2. Objekt erstellen (Execution)
    Portfolio portfolio;
    portfolio.addTrade(tradeInputData);
    
    // 3. Prüfen, ob Gewinn richtig ausgerechnet wurde
    // REQUIRE bricht den Test sofort ab, wenn die Bedingung nicht stimmt
    SECTION("Open trade, win bust be 0")
    {
        REQUIRE(portfolio.calculateTotalNetWin() == 0);
    }
    SECTION("Closed trade, there must be a win > 0")
    {
        auto& trade = portfolio.getTradesMutable();
        trade[0].setSellFee(40);
        trade[0].setSingleSellPrice(320);
        trade[0].setTax(40);
        trade[0].setSellDate(std::chrono::year(2026) / 6 / 5);
        trade[0].setTradeClosed(true);
        REQUIRE(portfolio.calculateTotalNetWin() == 110);
    }
    SECTION("Closed trade, there must be a win < 0")
    {
        auto& trade = portfolio.getTradesMutable();
        trade[0].setSellFee(40);
        trade[0].setSingleSellPrice(220);
        trade[0].setTax(40);
        trade[0].setSellDate(std::chrono::year(2026) / 6 / 5);
        trade[0].setTradeClosed(true);
        REQUIRE(portfolio.calculateTotalNetWin() == -890);
    }
}