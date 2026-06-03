#pragma once
#include <vector>

class Trade;

class ITradeRepository
{
public:
    virtual ~ITradeRepository() = default;
    virtual void saveData(const std::vector<Trade>& trades) = 0;
    virtual void readTrades(std::vector<Trade>& trades) = 0;
};
