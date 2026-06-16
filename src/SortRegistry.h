#pragma once
#include <functional>
#include <string>
#include <vector>

class Trade;

struct SortStrategy {
    std::string displayName;
    std::function<bool(const Trade&, const Trade&)> comparator;
};

class SortRegistry {
    static inline std::vector<SortStrategy> strategies;
public:
    static void registerStrategy(const std::string& name, auto comp) {
        strategies.push_back({name, comp});
    }
    static const auto& getStrategies() { return strategies; }
};