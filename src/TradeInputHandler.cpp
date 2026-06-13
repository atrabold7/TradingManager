#include "TradeInputHandler.h"
#include "TradePrinter.h"
#include "Portfolio.h"
#include <iostream>

#include "ITradeRepository.h"

void TradeInputHandler::run() {
    std::string input;
    int inputTradeField;
    bool isRunning = true;
    float totalWin = 0.0f;
    int inputMenuIndex;
    
    while (isRunning) {
        std::cout << "[1] Create trades" << std::endl;
        std::cout << "[2] Show trades" << std::endl;
        std::cout << "[3] Show calculation" << std::endl;
        std::cout << "[4] Load data" << std::endl;
        std::cout << "[5] Save data" << std::endl;
        std::cout << "[6] End" << std::endl;
        
        inputMenuIndex = readSaveInteger(6);
        if (inputMenuIndex == 0)
            continue;
        
        switch (inputMenuIndex)
        {
            case 1:
            getTradeInputData();
            break;
            
            case 2:
            changeDataInTrade();
            break;
            
            case 3:
            totalWin = m_portfolio.calculateTotalWin();
            displayTotalWin(totalWin);
            break;
            
            case 4:
            m_repository.readTrades(m_portfolio.getTradesMutable(), "portfolio.json");
            break;
            
            case 5:
            m_repository.saveData(m_portfolio.getTrades(), "portfolio.json");
            break;
            
            case 6:
            isRunning = false;
            break;
        }
    }
}
void TradeInputHandler::getTradeInputData()
{
    TradeInputData tradeInputData;
    tradeInputData.m_StockName = readString("Set stock name: ");
    tradeInputData.m_StockAmount = readFloat("Set stock quantity: ");
    tradeInputData.m_SingleBuyPrice = readFloat("Set single buy price: ");
    tradeInputData.m_Tax = readFloat("Set tax: ");
    tradeInputData.m_BuyFee = readFloat("Set fee: ");
    tradeInputData.m_BuyDate = readDate("Set buy date YYYY-MM-DD: ");
    
    tradeInputData.m_TradeClosed = false;
    
    m_portfolio.addTrade(tradeInputData);
    
    m_repository.saveData(m_portfolio.getTrades(), "portfolio.json");
}
void TradeInputHandler::displayTotalWin(float totalWin)
{
    std::cout << "Total Win: " << totalWin << std::endl;
}
float TradeInputHandler::readFloat(const std::string &command)
{
    float Data;
    std::string inputData;
    std::cout << command;
    size_t stopPos;
    
    while (true)
    {
        std::getline(std::cin, inputData);

        try
        {
            Data = std::stof(inputData, &stopPos);
            if (stopPos != inputData.length() || Data <= 0)
            {
                std::cout << "Only numbers > 0 are valid" << std::endl;
            }
            else
            {
                return Data;
            }
        }
        catch (...)
        {
            std::cout << "Only numbers are valid" << std::endl;
        }
    }
}
std::string TradeInputHandler::readString(const std::string &command)
{
    std::string inputData;
    std::cout << command;
    
    while (true)
    {
        std::getline(std::cin >> std::ws, inputData);
        if (inputData.empty())
        {
            std::cout << "Set a value" << std::endl;
        }
        else return inputData;
    }
}
std::chrono::year_month_day TradeInputHandler::readDate(const std::string &command)
{
    std::string inputString;
    std::chrono::year_month_day inputYear;
    
    while (true)
    {
        std::cout << command;
        
        std::getline(std::cin >> std::ws, inputString);
        std::istringstream ss{inputString};

        if (ss >> std::chrono::parse("%F", inputYear) && inputYear.ok()) {
            return inputYear;
        } else {
            std::cout << "Ungültiges Datum oder falsches Format. Bitte YYYY-MM-DD eingeben: ";
            std::cin.clear();
        }
    }
}
void TradeInputHandler::changeDataInTrade()
{
    TradeData tradeData;
    
    TradePrinter::printAll(m_portfolio);
    std::cout << std::endl << "Press valid trade number to change or press enter to leave: ";
    
    int indexTrade = readSaveInteger(m_portfolio.getTrades().size());
    if (indexTrade == 0)
        return;
    
    tradeData.sellFee = m_portfolio.getTrades()[indexTrade - 1].getSellFee();
    tradeData.singleSellPrice = m_portfolio.getTrades()[indexTrade - 1].getSingleSellPrice();
    tradeData.sellDate = m_portfolio.getTrades()[indexTrade - 1].getSellDate();
    tradeData.holdingPeriod = m_portfolio.getTrades()[indexTrade - 1].getHoldingPeriod();
    
    std::cout << std::endl << "[1] Sell Fee";
    std::cout << std::endl << "[2] Single Sell Price";
    std::cout << std::endl << "[3] Sell Date";
    std::cout << std::endl << "[4] Holding Period";
    std::cout << std::endl << "Press valid field number to change or enter to leave: ";
      
    int indexField = readSaveInteger(4);
    if (indexField == 0)
        return;
    
    switch (indexField)
    {
    case 1:                    
        tradeData.sellFee = readFloat("Set fee: ");
        break;
    case 2:
        tradeData.singleSellPrice = readFloat("Set single sell price: ");
        break;
    case 3:
        tradeData.sellDate = readDate("Set sell date YYYY-MM-DD: ");
        break;
    case 4:
        tradeData.holdingPeriod = readFloat("Set holding period: ");
        break;
    }
            
    m_portfolio.changeTrade(m_portfolio.getTradesMutable()[indexTrade - 1], tradeData);                
    
}
int TradeInputHandler::readSaveInteger(int maxIndex)
{
    std::string input;
    std::getline(std::cin, input);
    try
    {
        size_t stopPos;
        int index = std::stoi(input, &stopPos);
            
        if (stopPos == input.length() && index > 0 && index <= maxIndex)
        {
            return index;
        }
        else
        {
            std::cout << "Invalid input! Please enter a number in range." << std::endl;
        }
    }
    catch (...)
    {
        return 0;
    }
    return 0;
}