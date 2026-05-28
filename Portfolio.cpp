#include "Portfolio.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <format>
#include "TradeInputHandler.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void to_json(json& j, const Trade& t) {
    j = json{
            {"StockName", t.m_StockName},
            {"StockAmount", t.m_StockAmount},
            {"SingleBuyPrice", t.m_SingleBuyPrice},
            {"Tax", t.m_Tax},
            {"BuyFee", t.m_BuyFee},
            {"BuyDate", std::format("{:%F}", t.m_BuyDate)},
            {"SellDate", t.m_SellDate.has_value() ? std::format("{:%F}", t.m_SellDate.value()) : "null"},
            {"SingleSellPrice", t.m_SingleSellPrice},
            {"SellFee", t.m_SellFee},
            {"HoldingPeriod", t.m_HoldingPeriod},
            {"TradeClosed", t.m_TradeClosed}
    };
}

void from_json(const json& j, Trade& t) {
    j.at("StockName").get_to(t.m_StockName);
    j.at("StockAmount").get_to(t.m_StockAmount);
    j.at("SingleBuyPrice").get_to(t.m_SingleBuyPrice);
    j.at("Tax").get_to(t.m_Tax);
    j.at("BuyFee").get_to(t.m_BuyFee);
    
    std::string buyDateString;
    j.at("BuyDate").get_to(buyDateString);
    std::istringstream ss{buyDateString};
    ss >> std::chrono::parse("%F", t.m_BuyDate);
    
    std::string sellDateString;
    j.at("SellDate").get_to(sellDateString);
    if (!sellDateString.empty() && sellDateString != "null") {
        ss.clear();
        ss.str(sellDateString);
        std::chrono::year_month_day tempDate;
        ss >> std::chrono::parse("%F", tempDate);
        t.m_SellDate = tempDate;
    } else {
        t.m_SellDate = std::nullopt;
    }
    
    j.at("SingleSellPrice").get_to(t.m_SingleSellPrice);
    j.at("SellFee").get_to(t.m_SellFee);
    j.at("HoldingPeriod").get_to(t.m_HoldingPeriod);
    j.at("TradeClosed").get_to(t.m_TradeClosed);
}

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
void Portfolio::printAll() {
    
    std::cout << std::left << std::setw(20) << "Stock Name"
        << std::setw(15) << "Qty"
        << std::setw(15) << "Buy price"
        //<< " | Menge: " << std::setw(15) << m_BuyDate
        << std::setw(15) << "Sell price"
        //<< " | Menge: " << std::setw(15) << m_SellDate
        << std::setw(15) << "Hold time"
        << std::setw(15) << "Status"
        << std::endl << std::endl;

    for (const Trade& trade : m_trades) {
        std::cout << "==============================================================================================" << std::endl;
        trade.printTrade();
        }
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
    
    saveData();
}
void Portfolio::readTrades()
{
    std::ifstream file("portfolio_data.json");
    if (file.is_open()) {
        json j;
        file >> j;
        m_trades.clear();
        m_trades = j.get<std::vector<Trade>>();
        file.close();
    }
}
void Portfolio::saveData()
{
    std::ofstream file("portfolio_data.json");
    if (file.is_open()) {
        json j = m_trades;
        file << j.dump(4);
    }
}