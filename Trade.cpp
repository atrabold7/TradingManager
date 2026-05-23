#include "Trade.h"

void Trade::setSellFee(float SellFee) {
    m_SellFee = SellFee;
    }
void Trade::setSingleSellPrice(int SingleSellPrice) {
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
std::string Trade::getStockName() {
    return m_StockName;
    }
float Trade::getSingleBuyPrice() {
    return m_SingleBuyPrice;
    }
float Trade::getTax() {
    return m_Tax;
    }
float Trade::getBuyFee() {
    return m_BuyFee;
    }
float Trade::getStockAmount() {
    return m_StockAmount;
    }
float Trade::getSellFee() {
    return m_SellFee;
    }
std::chrono::year_month_day Trade::getBuyDate() {
    return m_BuyDate;
    }
float Trade::getSingleSellPrice() {
    return m_SingleSellPrice;
    }
std::chrono::year_month_day Trade::getSellDate() {
    return m_SellDate;
    }
int Trade::getHoldingPeriod() {
    return m_HoldingPeriod;
    }
bool Trade::getTradeClosed() {
    return m_TradeClosed;
    }