#pragma once
#include <string>
#include <chrono>
#include <optional>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Trade {
private:
    std::string m_StockName;
    float m_StockAmount = 0.0f;
    float m_SingleBuyPrice = 0.0f;
    float m_Tax = 0.0f;
    float m_BuyFee = 0.0f;
    std::chrono::year_month_day m_BuyDate;
    std::optional<std::chrono::year_month_day> m_SellDate;
    float m_SingleSellPrice = 0.0f;
    float m_SellFee = 0.0f;
    int m_HoldingPeriod = 0;
    bool m_TradeClosed = false;

    friend void to_json(json& j, const Trade& t);
    friend void from_json(const json& j, Trade& t);
public:
    Trade (const std::string &StockName, float StockAmount, float SingleBuyPrice, float Tax, float BuyFee, std::chrono::year_month_day BuyDate) :
        m_StockName(StockName), m_StockAmount(StockAmount), m_SingleBuyPrice(SingleBuyPrice), m_Tax(Tax), m_BuyFee(BuyFee),
        m_BuyDate(BuyDate) { }

    Trade() = default;
    
    void setSellFee(float SellFee);
    void setSingleSellPrice(float SingleSellPrice);
    void setSellDate(std::chrono::year_month_day SellDate);
    void setHoldingPeriod(int HoldingPeriod);
    void setTradeClosed(bool TradeClosed);

    std::string getStockName() const;
    float getStockAmount() const;
    float getSingleBuyPrice() const;
    float getTax() const;
    float getBuyFee() const;
    float getSellFee() const;
    std::chrono::year_month_day getBuyDate() const;
    float getSingleSellPrice() const;
    std::optional<std::chrono::year_month_day> getSellDate() const;
    int getHoldingPeriod() const;
    bool getTradeClosed() const;
    void printTrade(int StockId) const;
    };
