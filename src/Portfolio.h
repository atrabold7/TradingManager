#pragma once
#include <vector>
#include "Trade.h"

class Trade;

struct TradeInputData;

class Portfolio {
private:
    std::vector<Trade> m_trades;
public:
    void addTrade(TradeInputData tradeInputData);
    float calculateTotalWin();
    const std::vector<Trade>& getTrades() const;
    std::vector<Trade>& getTradesMutable();
    };