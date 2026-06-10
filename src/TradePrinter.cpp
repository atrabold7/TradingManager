#include "TradePrinter.h"
#include "Trade.h"
#include "Portfolio.h"
#include <iostream>
#include <iomanip>

void TradePrinter::printTrade(int StockId, const Trade &trade)
    {
    std::string SellDate;
    if (trade.getSellDate().has_value()) {
            std::stringstream ss;
            ss << trade.getSellDate().value();
            SellDate = ss.str();
        } else {
            SellDate = "";
        }
    
    std::cout << std::left << "[" << StockId << std::setw(4 - std::to_string(StockId).length()) << "]"
        << std::setw(15) << trade.getStockName()
        << std::setw(10) << trade.getStockAmount()
        << std::setw(15) << trade.getSingleBuyPrice()
        << std::setw(15) << trade.getBuyDate()
        << std::setw(15) << trade.getSingleSellPrice()
        << std::setw(15) << SellDate
        << std::setw(15) << trade.getHoldingPeriod()
        << std::setw(15) << (trade.getTradeClosed() ? "Closed" : "Open")
        << std::endl;
    }

void TradePrinter::printAll(const Portfolio& m_portfolio) {
    int StockId = 0;
    
    std::cout << std::left << std::setw(5) << "Id"
        << std::left << std::setw(15) << "Stock Name"
        << std::setw(10) << "Qty"
        << std::setw(15) << "Buy price"
        << std::setw(15) << "Buy date"
        << std::setw(15) << "Sell price"
        << std::setw(15) << "SellDate"
        << std::setw(15) << "Hold time"
        << std::setw(15) << "Status"
        << std::endl;

    for (const auto& trade : m_portfolio.getTrades()) {
        std::cout << "===============================================================================================================" << std::endl;
        TradePrinter::printTrade(++StockId, trade);
        }
    }