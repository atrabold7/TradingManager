#include "Portfolio.h"
#include <fstream>
#include "TradeInputHandler.h"

float Portfolio::calculateTotalNetWin() {
    float totalNetWin = 0;

    for (const Trade& trade : m_trades) {
        if (trade.getTradeClosed()) {
            float revenue = trade.getStockAmount() * trade.getSingleSellPrice();
            float expenses = trade.getStockAmount() * trade.getSingleBuyPrice()
                + trade.getSellFee()
                + trade.getTax()
                + trade.getBuyFee();

            totalNetWin += revenue - expenses;
            }
        }
    return totalNetWin;
    }
float Portfolio::calculateTotalGrossWin() {
    float totalGrossWin = 0;

    for (const Trade& trade : m_trades) {
        if (trade.getTradeClosed()) {
            float revenue = trade.getStockAmount() * trade.getSingleSellPrice();
            float expenses = trade.getStockAmount() * trade.getSingleBuyPrice();

            totalGrossWin += revenue - expenses;
        }
    }
    return totalGrossWin;
}
float Portfolio::calculateTotalFee() {
    float totalFee = 0;

    for (const Trade& trade : m_trades) {
        if (trade.getTradeClosed()) {
            totalFee += trade.getBuyFee() + trade.getSellFee();
        }
    }
    return totalFee;
}
float Portfolio::calculateTotalTax() {
    float totalTax = 0;

    for (const Trade& trade : m_trades) {
        if (trade.getTradeClosed()) {
            totalTax += trade.getTax();
        }
    }
    return totalTax;
}
void Portfolio::addTrade(TradeInputData tradeInputData)
{
    m_trades.emplace_back(
        tradeInputData.m_StockName,
        tradeInputData.m_StockAmount,
        tradeInputData.m_SingleBuyPrice,
        tradeInputData.m_BuyFee,
        tradeInputData.m_BuyDate);
}
const std::vector<Trade>& Portfolio::getTrades() const
{
    return m_trades;
}
std::vector<Trade>& Portfolio::getTradesMutable()
{
    return m_trades;
}
void Portfolio::changeTrade(Trade &trade, TradeData tradeData)
{
    trade.setSellFee(tradeData.sellFee);
    trade.setSingleSellPrice(tradeData.singleSellPrice);
    
    if (tradeData.sellDate.has_value())
        trade.setSellDate(tradeData.sellDate.value());
    
    trade.setTax(tradeData.tax);
    trade.setTradeClosed(true);
}