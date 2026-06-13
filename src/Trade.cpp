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
void Trade::setTax(float Tax) {
    m_Tax = Tax;
}
void Trade::setTradeClosed(bool TradeClosed) {
    m_TradeClosed = TradeClosed;
    }
const std::string& Trade::getStockName() const {
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
bool Trade::getTradeClosed() const {
    return m_TradeClosed;
    }
