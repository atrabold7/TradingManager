#pragma once
#include <string_view>

namespace Trading {
    static constexpr long long SCALE = 100000000;
    static constexpr std::string_view FILESTOCKS {"portfolio_stock.json"};
    static constexpr std::string_view FILESCRYPTO {"portfolio_crypto.json"};
    
    // helper method
    inline double longlongToDisplay(long long value)
    {
        return static_cast<double>(value) / SCALE;
    }
}