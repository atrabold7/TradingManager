#pragma once
#include <vector>
#include "Trade.h"

struct TradeData
{
    std::optional<std::chrono::year_month_day> sellDate;
    long long singleSellPrice = 0;
    long long sellFee = 0;
    long long tax = 0;
    bool tradeClosed = false;
};

class Trade;

struct TradeInputData;

class Portfolio {
private:
    std::vector<Trade> m_trades;
public:
    void addTrade(const TradeInputData &tradeInputData);
    void changeTrade(Trade &trade, TradeData tradeData);
    long long calculateTotalNetWin() const;
    long long calculateTotalGrossWin() const ;
    long long calculateTotalFee();
    long long calculateTotalTax();
    const std::vector<Trade>& getTrades() const;
    std::vector<Trade>& getTradesMutable();
    };