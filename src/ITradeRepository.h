#pragma once
#include <vector>

class Trade;

class ITradeRepository
{
public:
    virtual ~ITradeRepository() = default;
    virtual bool saveData(const std::vector<Trade>& trades, const char* filename) = 0;
    virtual bool readTrades(std::vector<Trade>& trades, const char* filename) = 0;
};
