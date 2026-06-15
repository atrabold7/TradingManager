// TradingManager.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "Portfolio.h"
#include "FileTradeRepository.h"
#include "TradeInputHandler.h"
#include "TradingConstants.h"

int main()
{
    Portfolio portfolio;
    auto repo = std::make_unique<FileTradeRepository>(std::string(Trading::FILESTOCKS));
    
    TradeInputHandler tradeInputHandler(portfolio, *repo);
    
    tradeInputHandler.run();

    }