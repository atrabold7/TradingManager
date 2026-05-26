#include "Portfolio.h"
#include <iomanip>
#include <iostream>
#include "TradeInputHandler.h"

float Portfolio::calculateTotalWin() {
    float totalWin = 0;

    for (const Trade& trade : m_trades) {
        if (trade.getTradeClosed()) {
            float revenue = trade.getStockAmount() * trade.getSingleSellPrice();
            float expenses = trade.getStockAmount() * trade.getSingleBuyPrice()
                + trade.getSellFee()
                + trade.getTax()
                + trade.getBuyFee();

            totalWin += revenue - expenses;
            }
        }

    return totalWin;
    }
void Portfolio::printAll() {
    
    std::cout << std::left << std::setw(20) << "Stock Name"
        << std::setw(15) << "Qty"
        << std::setw(15) << "Buy price"
        //<< " | Menge: " << std::setw(15) << m_BuyDate
        << std::setw(15) << "Sell price"
        //<< " | Menge: " << std::setw(15) << m_SellDate
        << std::setw(15) << "Hold time"
        << std::setw(15) << "Status"
        << std::endl << std::endl;

    for (const Trade& trade : m_trades) {
        std::cout << "==============================================================================================" << std::endl;
        trade.printTrade();
        }
    }
void Portfolio::addTrade(TradeInputData tradeInputData)
{
    m_trades.emplace_back(
        tradeInputData.m_StockName,
        tradeInputData.m_StockAmount,
        tradeInputData.m_SingleBuyPrice,
        tradeInputData.m_Tax,
        tradeInputData.m_BuyFee,
        tradeInputData.m_BuyDate);
}
void Portfolio::generateTestTrades() {
    m_trades.emplace_back("Alphabet", 9, 335.6, 3, 6, std::chrono::year(2026) / 11 / 11);
    m_trades.emplace_back("BYD", 290, 11.73, 3, 6, std::chrono::year(2026) / 11 / 11);
    m_trades.emplace_back("OMV", 99, 61.75, 3, 6, std::chrono::year(2026) / 11 / 11);
    m_trades.emplace_back("Rheinmetall", 7, 1381.65, 3, 6, std::chrono::year(2026) / 11 / 11);
    m_trades.emplace_back("BYD", 230, 11.73, 3, 6, std::chrono::year(2026) / 11 / 11);
    }