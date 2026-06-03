#include "FileTradeRepository.h"
#include "TradeSerializer.h"
#include "Trade.h"
#include <fstream>

void FileTradeRepository::readTrades(std::vector<Trade>& trades)
{
    std::ifstream file("portfolio_data.json");
    if (file.is_open()) {
        TradeSerializer::readTrades(file, trades);
        file.close();
    }
}
void FileTradeRepository::saveData(const std::vector<Trade>& trades)
{
    std::ofstream file("portfolio_data.json");
    if (file.is_open()) {
        TradeSerializer::saveData(file, trades);
    }
}
