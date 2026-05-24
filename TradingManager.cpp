// TradingManager.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "Trade.h"
#include <vector>

void GenerateTestTrades(std::vector<Trade> &trade) {
    Trade trade1("Alphabet", 9, 11.5, 3, 6, std::chrono::year(2026) / 11 / 11);
    trade.push_back(trade1);
    }

float CalculateWin(std::vector<Trade> &trades) {
    float totalWin = 0;

    for (const Trade &trade : trades) {
        if (trade.getTradeClosed()) {
            float revenue = trade.getStockAmount() * trade.getSingleSellPrice();
            float expenses = trade.getStockAmount() * trade.getSingleBuyPrice()
                + trade.getSellFee()
                + trade.getTax()
                + trade.getBuyFee();

            totalWin += revenue - expenses;
            }
        }

    return totalWin;
    }

int main()
{
    std::vector<Trade> Trades;

    // generate trades
    GenerateTestTrades(Trades);
    }