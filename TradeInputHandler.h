#pragma once
#include <chrono>

class Portfolio;

struct TradeInputData
{
    std::string m_StockName;
    float m_StockAmount = 0.0f;
    float m_SingleBuyPrice = 0.0f;
    float m_Tax = 0.0f;
    float m_BuyFee = 0.0f;
    std::chrono::year_month_day m_BuyDate;
    bool m_TradeClosed = false;
};

class TradeInputHandler {
private:
    Portfolio &m_portfolio;

public:
    TradeInputHandler(Portfolio &portfolio) :
        m_portfolio(portfolio) {}
    void run();
    void getTradeInputData();
    float readFloat(const std::string &command);
    std::string readString(const std::string &command);
    std::chrono::year_month_day readDate(const std::string &command);
    void displayTotalWin(float totalWin);
    };