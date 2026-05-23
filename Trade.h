#pragma once

#include <string>
#include <chrono>
#include <iostream>

class Trade {
private:
    std::string m_StockName;
    float m_StockAmount = 0.0f;
    float m_SingleBuyPrice = 0.0f;
    float m_Tax = 0.0f;
    float m_BuyFee = 0.0f;
    float m_SellFee = 0.0f;
    std::chrono::year_month_day m_BuyDate;
    float m_SingleSellPrice = 0.0f;
    std::chrono::year_month_day m_SellDate;
    int m_HoldingPeriod = 0;
    bool m_TradeClosed = false;

public:
    Trade (const std::string &StockName, float StockAmount, float SingleBuyPrice, float Tax, float BuyFee, float SellFee, std::chrono::year_month_day BuyDate) :
        m_StockName(StockName), m_StockAmount(StockAmount), m_SingleBuyPrice(SingleBuyPrice), m_Tax(Tax), m_BuyFee(BuyFee),
        m_SellFee(SellFee), m_BuyDate(BuyDate) { }

    void setSellFee(float SellFee);
    void setSingleSellPrice(int SingleSellPrice);
    void setSellDate(std::chrono::year_month_day SellDate);
    void setHoldingPeriod(int HoldingPeriod);
    void setTradeClosed(bool TradeClosed);

    std::string getStockName();
    float getStockAmount();
    float getSingleBuyPrice();
    float getTax();
    float getBuyFee();
    float getSellFee();
    std::chrono::year_month_day getBuyDate();
    float getSingleSellPrice();
    std::chrono::year_month_day getSellDate();
    int getHoldingPeriod();
    bool getTradeClosed();

    };
