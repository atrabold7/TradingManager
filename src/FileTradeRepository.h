#pragma once
#include "ITradeRepository.h"

class FileTradeRepository : public ITradeRepository
{
public:
    virtual bool saveData(const std::vector<Trade>& trades, const char* filename) override;
    virtual bool readTrades(std::vector<Trade>& trades, const char* filename) override;
};
