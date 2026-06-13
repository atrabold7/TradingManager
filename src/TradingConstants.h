#pragma once

namespace Trading {
    static constexpr long long SCALE = 1000;
    
    // helper method
    inline double longlongToDisplay(long long value)
    {
        return static_cast<double>(value) / SCALE;
    }
}