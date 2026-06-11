#include "TradeInputHandler.h"
#include "TradePrinter.h"
#include "Portfolio.h"
#include <iostream>

#include "ITradeRepository.h"

void TradeInputHandler::run() {
    int input;
    int inputTradeIndex;
    int inputTradeField;
    int inputValue;
    bool isRunning = true;
    float totalWin = 0.0f;
    TradeData tradeData;
    
    while (isRunning) {
        std::cout << "[1] Create trades" << std::endl;
        std::cout << "[2] Show trades" << std::endl;
        std::cout << "[3] Show calculation" << std::endl;
        std::cout << "[4] Load data" << std::endl;
        std::cout << "[5] Save data" << std::endl;
        std::cout << "[6] End" << std::endl;
        
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue;
            }

        switch (input) {
            case 1:
                getTradeInputData();
                break;
            case 2:
                TradePrinter::printAll(m_portfolio);
                std::cout << std::endl << "Press valid tade number to change or enter to leave: ";
                if (!(std::cin >> inputTradeIndex)) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Invalid input! Please enter a number." << std::endl;
                    continue;
                }
            
                tradeData.sellFee = m_portfolio.getTrades()[inputTradeIndex].getSellFee();
                tradeData.singleSellPrice = m_portfolio.getTrades()[inputTradeIndex].getSingleSellPrice();
                tradeData.sellDate = m_portfolio.getTrades()[inputTradeIndex].getSellDate();
                tradeData.holdingPeriod = m_portfolio.getTrades()[inputTradeIndex].getHoldingPeriod();
            
                std::cout << std::endl << "[1] Sell Fee";
                std::cout << std::endl << "[2] Single Sell Price";
                std::cout << std::endl << "[3] Sell Date";
                std::cout << std::endl << "[4] Holding Period";
                std::cout << std::endl << "Press valid field number to change or enter to leave: ";
                if (!(std::cin >> inputTradeField)) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Invalid input! Please enter a number." << std::endl;
                    continue;
                }
            
                std::cout << std::endl << "Enter value: ";
                if (!(std::cin >> inputValue)) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Invalid input! Please enter a number." << std::endl;
                    continue;
                }
            
                switch (inputTradeField)
                {
                case 1:
                    tradeData.sellFee = inputValue;
                    break;
                case 2:
                    tradeData.singleSellPrice = inputValue;
                    break;
                case 3:
                    //tradeData.sellDate = inputValue;
                    break;
                case 4:
                    tradeData.holdingPeriod = inputValue;
                    break;
                }
            
                m_portfolio.changeTrade(m_portfolio.getTradesMutable()[inputTradeIndex - 1], tradeData);
            
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
            default:
                std::cout << "Wrong input. Please use only valid numbers" << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
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
    float inputData;
    std::cout << command;
    
    while (true)
    {
        if (std::cin >> inputData)
        {
            if (inputData <= 0)
            {
                std::cout << "Only numbers > 0 are valid" << std::endl;
            }
            else
            {
                return inputData;
            }
        }
        else
        {
            std::cout << "Only numbers are valid" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
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