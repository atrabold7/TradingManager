cmake_minimum_required(VERSION 3.14)
project(TradingManager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Globales Laden der Libs, damit sie überall verfügbar sind
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v3.4.0)
FetchContent_MakeAvailable(json Catch2)

# Haupt-App (wird später in den src Ordner verschoben)
add_executable(TradingManager
        src/TradingManager.cpp
        src/Trade.cpp
        src/Portfolio.cpp
        src/FileTradeRepository.cpp
        src/TradeInputHandler.cpp
        src/TradePrinter.cpp
        src/TradeSerializer.cpp
        src/Portfolio.h
        src/TradePrinter.h
        src/FileTradeRepository.h
        src/TradeSerializer.h
        src/ITradeRepository.h
        src/Trade.h
        src/TradeInputHandler.h
        src/TradingConstants.h
        src/SortRegistry.h
)
target_link_libraries(TradingManager PRIVATE nlohmann_json::nlohmann_json)

# Test-Ordner einbinden
enable_testing()
add_subdirectory(tests)