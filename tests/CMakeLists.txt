add_executable(unit_tests
        test_trade.cpp
        ../src/Trade.cpp
)

# Hier fügen wir den src-Ordner zum Include-Pfad hinzu
target_include_directories(unit_tests PRIVATE ../src)

target_link_libraries(unit_tests
        PRIVATE
        Catch2::Catch2WithMain
        nlohmann_json::nlohmann_json
)