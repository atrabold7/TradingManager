#include "Trade.h"
#include <iostream>

void Trade::setSellFee(long long SellFee) {
    m_SellFee = SellFee;
    }
void Trade::setSingleSellPrice(long long SingleSellPrice) {
    m_SingleSellPrice = SingleSellPrice;
    }
void Trade::setSellDate(std::chrono::year_month_day SellDate) {
    m_SellDate = SellDate;
    }
void Trade::setTax(long long Tax) {
    m_Tax = Tax;
}
void Trade::setTradeClosed(bool TradeClosed) {
    m_TradeClosed = TradeClosed;
    }
const std::string& Trade::getStockName() const {
    return m_StockName;
    }
long long Trade::getSingleBuyPrice() const {
    return m_SingleBuyPrice;
    }
long long Trade::getTax() const {
    return m_Tax;
    }
long long Trade::getBuyFee() const {
    return m_BuyFee;
    }
long long Trade::getStockAmount() const {
    return m_StockAmount;
    }
long long Trade::getSellFee() const {
    return m_SellFee;
    }
std::chrono::year_month_day Trade::getBuyDate() const {
    return m_BuyDate;
    }
long long Trade::getSingleSellPrice() const {
    return m_SingleSellPrice;
    }
std::optional<std::chrono::year_month_day> Trade::getSellDate() const {
    return m_SellDate;
    }
bool Trade::getTradeClosed() const {
    return m_TradeClosed;
    }
