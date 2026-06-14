#pragma once
#include <chrono>
#include <string>

class FileTradeRepository;
class Portfolio;
class ITradeRepository;

struct TradeInputData
{
    std::string m_StockName;
    float m_StockAmount = 0.0f;
    float m_SingleBuyPrice = 0.0f;
    float m_BuyFee = 0.0f;
    std::chrono::year_month_day m_BuyDate;
    bool m_TradeClosed = false;
};

class TradeInputHandler {
private:
    Portfolio &m_portfolio;
    ITradeRepository &m_repository; // Hier das Repository injizieren
    
public:
    TradeInputHandler(Portfolio &portfolio, ITradeRepository &repository) :
        m_portfolio(portfolio), m_repository(repository) {}
    void run();
    void getTradeInputData();
    std::optional<long long> readLongLong(const std::string &command);
    std::optional<std::string> readString(const std::string &command);
    std::optional<std::chrono::year_month_day> readDate(const std::string &command);
    void displayPerformanceReport(long long totalGrossWin, long long totalFee, long long totalTax, long long totalNetWin);
    int readSaveInteger(int maxIndex);
    void changeDataInTrade();
    void clearConsole();
    };