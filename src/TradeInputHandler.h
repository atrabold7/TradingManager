#pragma once
#include <chrono>
#include <string>

#include "SortRegistry.h"
#include "Trade.h"

class FileTradeRepository;
class Portfolio;
class ITradeRepository;

struct TradeInputData
{
    std::string m_StockName;
    long long m_StockAmount = 0;
    long long m_SingleBuyPrice = 0;
    long long m_BuyFee = 0;
    std::chrono::year_month_day m_BuyDate;
    bool m_TradeClosed = false;
};

class TradeInputHandler {
private:
    Portfolio &m_portfolio;
    ITradeRepository &m_repository; // Hier das Repository injizieren
    
public:
    TradeInputHandler(Portfolio &portfolio, ITradeRepository &repository) :
        m_portfolio(portfolio), m_repository(repository)
    {
        SortRegistry::registerStrategy("Asset Name", [](const Trade &trade1, const Trade &trade2)
            {return trade1.getStockName() < trade2.getStockName();});
        SortRegistry::registerStrategy("Quantity", [](const Trade &trade1, const Trade &trade2)
            {return trade1.getStockAmount() < trade2.getStockAmount();});
        SortRegistry::registerStrategy("Buy Date", [](const Trade &trade1, const Trade &trade2)
            {return trade1.getBuyDate() < trade2.getBuyDate();});
        SortRegistry::registerStrategy("Sell Date", [](const Trade &trade1, const Trade &trade2)
        {
            if (!trade1.getSellDate() && !trade2.getSellDate()) return false;
            if (!trade1.getSellDate()) return false;
            if (!trade2.getSellDate()) return true;
            return trade1.getSellDate().value() < trade2.getSellDate().value();
        });
        SortRegistry::registerStrategy("Holt Time", [](const Trade &trade1, const Trade &trade2)
        {
            if (!trade1.getSellDate() && !trade2.getSellDate()) return false;
            if (!trade1.getSellDate()) return false;
            if (!trade2.getSellDate()) return true;
            auto holtTime1 = std::chrono::sys_days(trade1.getSellDate().value())
            - std::chrono::sys_days(trade1.getBuyDate());
            auto holtTime2 = std::chrono::sys_days(trade2.getSellDate().value())
            - std::chrono::sys_days(trade2.getBuyDate());

            return holtTime1 < holtTime2;
        });
        SortRegistry::registerStrategy("Status", [](const Trade &trade1, const Trade &trade2)
            {return trade1.getTradeClosed() > trade2.getTradeClosed();});
    }
    void run();
    void getTradeInputData();
    std::optional<long long> readLongLong(const std::string &command);
    std::optional<std::string> readString(const std::string &command);
    std::optional<std::chrono::year_month_day> readDate(const std::string &command);
    void displayPerformanceReport(long long totalGrossWin, long long totalFee, long long totalTax, long long totalNetWin);
    int readSaveInteger(int maxIndex);
    void changeDataInTrade();
    void sortAssets();
    void clearConsole();
    };