// TradingManager.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "Portfolio.h"
#include "FileTradeRepository.h"
#include "TradeInputHandler.h"

int main()
{
    int input;
    Portfolio portfolio;
    auto repo = std::make_unique<FileTradeRepository>();
    
    TradeInputHandler tradeInputHandler(portfolio, *repo);
    
    tradeInputHandler.run();

    }