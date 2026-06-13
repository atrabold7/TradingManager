#pragma once
#include <vector>
#include "Trade.h"

struct TradeData
{
    std::optional<std::chrono::year_month_day> sellDate;
    float singleSellPrice = 0.0f;
    float sellFee = 0.0f;
    int holdingPeriod = 0;
    bool tradeClosed = false;
};

class Trade;

struct TradeInputData;

class Portfolio {
private:
    std::vector<Trade> m_trades;
public:
    void addTrade(TradeInputData tradeInputData);
    void changeTrade(Trade &trade, TradeData tradeData);
    float calculateTotalWin();
    const std::vector<Trade>& getTrades() const;
    std::vector<Trade>& getTradesMutable();
    };