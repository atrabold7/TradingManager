#pragma once
#include "ITradeRepository.h"
#include <string>

class FileTradeRepository : public ITradeRepository
{
private:
    std::string m_fileNameStock;
public:
    FileTradeRepository(std::string fileNameStock) : m_fileNameStock(fileNameStock) {};
    
    virtual bool saveData(const std::vector<Trade>& trades) override;
    virtual bool readTrades(std::vector<Trade>& trades) override;
};
