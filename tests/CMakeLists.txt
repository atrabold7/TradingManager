# 1. Den Pfad zu deinen Quellcode-Dateien im 'src' Ordner hinzufügen
#    Damit findet der Compiler die Header (Trade.h, etc.) ohne ../../-Gefrickel
include_directories(../src)

# 2. Das Test-Programm definieren
#    Hier listen wir die Test-Datei und die zu testende Klasse auf
add_executable(unit_tests
        ../src/Trade.cpp
        ../src/Portfolio.cpp
        ../src/TradeSerializer.cpp
        ../src/FileTradeRepository.cpp
        test_trade.cpp
        test_portfolio.cpp
        test_tradeserializer.cpp
        test_filetraderepository.cpp
)

# 3. Verknüpfung mit den Libraries
#    Das 'Catch2::Catch2WithMain' Ziel existiert, weil es im Root-CMake
#    per FetchContent geladen wurde.
target_link_libraries(unit_tests
        PRIVATE
        Catch2::Catch2WithMain
        nlohmann_json::nlohmann_json
)

# 4. Test registrieren
add_test(NAME AllTests COMMAND unit_tests)