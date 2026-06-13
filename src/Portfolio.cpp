#include "Portfolio.h"
#include <fstream>
#include "TradeInputHandler.h"
#include "TradingConstants.h"

long long Portfolio::calculateTotalNetWin() {
    long long totalNetWin {0};

    for (const Trade& trade : m_trades) {
        if (trade.getTradeClosed()) {
            long long revenue = Trading::longlongToDisplay(trade.getStockAmount() * trade.getSingleSellPrice());
            long long expenses = Trading::longlongToDisplay(trade.getStockAmount() * trade.getSingleBuyPrice())
                + trade.getSellFee()
                + trade.getTax()
                + trade.getBuyFee();

            totalNetWin += revenue - expenses;
            }
        }
    return totalNetWin;
    }
long long Portfolio::calculateTotalGrossWin() {
    long long totalGrossWin {0};

    for (const Trade& trade : m_trades) {
        if (trade.getTradeClosed()) {
            long long revenue = Trading::longlongToDisplay(trade.getStockAmount() * trade.getSingleSellPrice());
            long long expenses = Trading::longlongToDisplay(trade.getStockAmount() * trade.getSingleBuyPrice());

            totalGrossWin += revenue - expenses;
        }
    }
    return totalGrossWin;
}
long long Portfolio::calculateTotalFee() {
    long long totalFee = std::accumulate(m_trades.begin(), m_trades.end(), 0LL, 
    [](long long sum, const Trade& trade) {
        if (trade.getTradeClosed())
        {
            return sum + trade.getBuyFee() + trade.getSellFee();    
        }
        else
        {
            return sum;
        }
    });
    
    return totalFee;
}
long long Portfolio::calculateTotalTax() {
    long long totalTax = std::accumulate(m_trades.begin(), m_trades.end(), 0LL, 
    [](long long sum, const Trade& trade) {
        if (trade.getTradeClosed())
        {
            return sum + trade.getTax();   
        }
        else
        {
            return sum;
        }
    });
    
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