#include "Portfolio.h"
#include <fstream>
#include "TradeInputHandler.h"

float Portfolio::calculateTotalWin() {
    float totalWin = 0;

    for (const Trade& trade : m_trades) {
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
void Portfolio::addTrade(TradeInputData tradeInputData)
{
    m_trades.emplace_back(
        tradeInputData.m_StockName,
        tradeInputData.m_StockAmount,
        tradeInputData.m_SingleBuyPrice,
        tradeInputData.m_Tax,
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
        
    trade.setHoldingPeriod(tradeData.holdingPeriod);
    trade.setTradeClosed(true);
}