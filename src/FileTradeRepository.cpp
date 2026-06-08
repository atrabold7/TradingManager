#include "FileTradeRepository.h"
#include "TradeSerializer.h"
#include "Trade.h"
#include <fstream>

bool FileTradeRepository::readTrades(std::vector<Trade>& trades, const char* filename)
{
    std::ifstream file(filename);
    if (file.is_open()) {
        TradeSerializer::readTrades(file, trades);
        file.close();
        return true;
    }
    return false;
}
bool FileTradeRepository::saveData(const std::vector<Trade>& trades, const char* filename)
{
    std::ofstream file(filename);
    if (file.is_open()) {
        TradeSerializer::saveData(file, trades);
        return true;
    }
    return false;
}
