cmake_minimum_required(VERSION 3.14)
project(TradingManager)

# C++ Standard auf 17 setzen
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JSON Bibliothek holen
include(FetchContent)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Hier kommen alle deine .cpp Dateien rein
# Sobald du eine neue Datei erstellst, schreibst du sie einfach hier dazu
add_executable(TradingManager 
    TradingManager.cpp 
    Trade.cpp
 "Portfolio.cpp" "Portfolio.h" "TradeInputHandler.cpp" "TradeInputHandler.h"
        Trade.h)

# Das verbindet dein Programm mit der JSON-Bibliothek
target_link_libraries(TradingManager PRIVATE nlohmann_json::nlohmann_json)