#pragma once
#include <string>
#include <chrono>
#include <optional>
#include <nlohmann/json.hpp>

class Trade;
using json = nlohmann::json;

void to_json(json& j, const Trade& t);
void from_json(const json& j, Trade& t);

class Trade {
private:
    std::string m_StockName;
    long long m_StockAmount {0};
    long long m_SingleBuyPrice {0};
    long long m_BuyFee {0};
    std::chrono::year_month_day m_BuyDate;
    std::optional<std::chrono::year_month_day> m_SellDate;
    long long m_SingleSellPrice {0};
    long long m_SellFee {0};
    long long m_Tax = {0};
    bool m_TradeClosed = false;
    
    friend void to_json(json& j, const Trade& t);
    friend void from_json(const json& j, Trade& t);
    
public:
    Trade (const std::string &StockName, long long StockAmount, long long SingleBuyPrice, long long BuyFee, std::chrono::year_month_day BuyDate) :
        m_StockName(StockName), m_StockAmount(StockAmount), m_SingleBuyPrice(SingleBuyPrice), m_BuyFee(BuyFee),
        m_BuyDate(BuyDate) { }
    
    bool operator==(const Trade& trade1) const = default;

    Trade() = default;
    
    void setSellFee(long long SellFee);
    void setSingleSellPrice(long long SingleSellPrice);
    void setSellDate(std::chrono::year_month_day SellDate);
    void setTax(long long Tax);
    void setTradeClosed(bool TradeClosed);

    const std::string& getStockName() const;
    long long getStockAmount() const;
    long long getSingleBuyPrice() const;
    long long getTax() const;
    long long getBuyFee() const;
    long long getSellFee() const;
    std::chrono::year_month_day getBuyDate() const;
    long long getSingleSellPrice() const;
    std::optional<std::chrono::year_month_day> getSellDate() const;
    bool getTradeClosed() const;
    };
