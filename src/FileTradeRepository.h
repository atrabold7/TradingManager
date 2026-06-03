#pragma once
#include "ITradeRepository.h"

class FileTradeRepository : public ITradeRepository
{
public:
    virtual void saveData(const std::vector<Trade>& trades) override;
    virtual void readTrades(std::vector<Trade>& trades) override;
};
