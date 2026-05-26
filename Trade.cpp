#include "Trade.h"
#include <iostream>

void Trade::setSellFee(float SellFee) {
    m_SellFee = SellFee;
    }
void Trade::setSingleSellPrice(float SingleSellPrice) {
    m_SingleSellPrice = SingleSellPrice;
    }
void Trade::setSellDate(std::chrono::year_month_day SellDate) {
    m_SellDate = SellDate;
    }
void Trade::setHoldingPeriod(int HoldingPeriod) {
    m_HoldingPeriod = HoldingPeriod;
    }
void Trade::setTradeClosed(bool TradeClosed) {
    m_TradeClosed = TradeClosed;
    }
std::string Trade::getStockName() const {
    return m_StockName;
    }
float Trade::getSingleBuyPrice() const {
    return m_SingleBuyPrice;
    }
float Trade::getTax() const {
    return m_Tax;
    }
float Trade::getBuyFee() const {
    return m_BuyFee;
    }
float Trade::getStockAmount() const {
    return m_StockAmount;
    }
float Trade::getSellFee() const {
    return m_SellFee;
    }
std::chrono::year_month_day Trade::getBuyDate() const {
    return m_BuyDate;
    }
float Trade::getSingleSellPrice() const {
    return m_SingleSellPrice;
    }
std::optional<std::chrono::year_month_day> Trade::getSellDate() const {
    return m_SellDate;
    }
int Trade::getHoldingPeriod() const {
    return m_HoldingPeriod;
    }
bool Trade::getTradeClosed() const {
    return m_TradeClosed;
    }
void Trade::printTrade() const
    {
    std::cout << std::left << std::setw(20) << m_StockName
        << std::setw(15) << m_StockAmount
        << std::setw(15) << m_SingleBuyPrice
        //<< " | Menge: " << std::setw(15) << m_BuyDate
        << std::setw(15) << m_SingleSellPrice
        //<< " | Menge: " << std::setw(15) << m_SellDate
        << std::setw(15) << m_HoldingPeriod
        << std::setw(15) << m_TradeClosed
        << std::endl;
    }