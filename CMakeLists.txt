cmake_minimum_required(VERSION 3.14)
project(TradingManager)

# C++ Standard auf 20 setzen (Wichtig für std::chrono)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JSON Bibliothek holen
include(FetchContent)
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)


# =====================================================================
# === NEU: Catch2 Test-Framework von GitHub laden =====================
# =====================================================================
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)
# =====================================================================


# Hier kommen alle deine .cpp Dateien rein
# Sobald du eine neue Datei erstellst, schreibst du sie einfach hier dazu
add_executable(TradingManager
        TradingManager.cpp
        Trade.cpp
        "Portfolio.cpp"
        "Portfolio.h"
        "TradeInputHandler.cpp"
        "TradeInputHandler.h"
        Trade.h
        TradePrinter.cpp
        TradePrinter.h
        ITradeRepository.h
        FileTradeRepository.h
        FileTradeRepository.cpp
        TradeSerializer.cpp
        TradeSerializer.h
)

# Das verbindet dein Programm mit der JSON-Bibliothek
target_link_libraries(TradingManager PRIVATE nlohmann_json::nlohmann_json)


# =====================================================================
# === NEU: Das Test-Programm (unit_tests) erstellen ===================
# =====================================================================
# WICHTIG: Hier listen wir nur die Test-Datei und die zu testende Klasse auf.
# Keine 'TradingManager.cpp', damit es nicht zu zwei main()-Funktionen kommt!
add_executable(unit_tests
        test_trade.cpp
        Trade.cpp
)

# Wir verknüpfen die Tests mit Catch2 und der JSON-Bibliothek
target_link_libraries(unit_tests
        PRIVATE
        Catch2::Catch2WithMain
        nlohmann_json::nlohmann_json
)
# =====================================================================
