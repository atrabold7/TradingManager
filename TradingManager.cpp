// TradingManager.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "Portfolio.h"
#include "TradeInputHandler.h"

int main()
{
    int input;
    Portfolio portfolio;
    TradeInputHandler tradeInputHandler(portfolio);
    
    tradeInputHandler.run();

    }