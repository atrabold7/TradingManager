#pragma once
#include <nlohmann/json.hpp>
#include "Trade.h"

using json = nlohmann::json;

namespace TradeSerializer
{
    void to_json(json& j, const Trade& t);
    void from_json(const json& j, Trade& t);
    void readTrades(std::istream& file, std::vector<Trade>& trades);
    void saveData(std::ostream& file, const std::vector<Trade>& trades);
}