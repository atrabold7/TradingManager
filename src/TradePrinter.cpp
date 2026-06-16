#include "TradePrinter.h"
#include "TradingConstants.h"
#include "Trade.h"
#include "Portfolio.h"
#include <iostream>
#include <iomanip>

void TradePrinter::printTrade(int StockId, const Trade &trade)
    {
    std::string SellDate;
    std::string holdTimePrint;
    
    if (trade.getSellDate().has_value()) {
        std::stringstream ss;
        ss << trade.getSellDate().value();
        SellDate = ss.str();
        
        std::chrono::sys_days sysBuyDate{trade.getBuyDate()};
        std::chrono::sys_days sysSellDate{trade.getSellDate().value()};
        std::chrono::days diffDays = sysSellDate - sysBuyDate;
        
        holdTimePrint = std::to_string(diffDays.count());
        }
    else {
            SellDate = "";
        holdTimePrint = "";
        }
    
    std::cout << std::left << "[" << StockId << std::setw(4 - static_cast<int>(std::to_string(StockId).length())) << "]"
        << std::setw(13) << trade.getStockName()
        << std::right << std::fixed << std::setprecision(8) << std::setw(15) << Trading::longlongToDisplay(trade.getStockAmount())
        << std::setprecision(2) << std::setw(15) << Trading::longlongToDisplay(trade.getSingleBuyPrice())
        << std::setw(15) << trade.getBuyDate()
        << std::setw(15) << Trading::longlongToDisplay(trade.getSingleSellPrice())
        << std::setw(15) << SellDate
        << std::setw(15) << holdTimePrint
        << std::setw(12) << (trade.getTradeClosed() ? "Closed" : "Open")
        << "\n";
    }

void TradePrinter::printAll(const Portfolio& m_portfolio) {
    int StockId = 0;
    
    std::cout << std::left << std::setw(5) << "Id"
        << std::left << std::setw(25) << "Stock Name"
        << std::setw(9) << "Qty"
        << std::setw(16) << "Buy price"
        << std::setw(13) << "Buy date"
        << std::setw(16) << "Sell price"
        << std::setw(15) << "Sell Date"
        << std::setw(15) << "Hold time"
        << std::setw(15) << "Status"
        << "\n";

    for (const auto& trade : m_portfolio.getTrades()) {
        std::cout << "========================================================================================================================" << "\n";
        TradePrinter::printTrade(++StockId, trade);
        }
    }