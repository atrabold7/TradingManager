#pragma once
#include <vector>
#include "Trade.h"

class Trade;

struct TradeInputData;

class Portfolio {
private:
    std::vector<Trade> m_trades;
public:
    float calculateTotalWin();
    void printAll();
    void addTrade(TradeInputData tradeInputData);
    void generateTestTrades();
    void saveData();
    };