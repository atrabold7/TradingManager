#include "TradeSerializer.h"
#include <fstream>

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
    j.at("TradeClosed").get_to(t.m_TradeClosed);
}

namespace TradeSerializer
{
    void readTrades(std::istream& file, std::vector<Trade>& trades)
    {
        json j;
        file >> j;
        trades.clear();
        trades = j.get<std::vector<Trade>>();
    }
    void saveData(std::ostream& file, const std::vector<Trade>& trades)
    {
        json j = trades;
        file << j.dump(4);
    }
}
