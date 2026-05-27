#include "TradeInputHandler.h"
#include "Portfolio.h"
#include <iostream>

void TradeInputHandler::run() {
    int input;
    bool isRunning = true;
    m_portfolio.generateTestTrades();

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
                m_portfolio.printAll();
                break;
            case 3:

                break;
            case 4:
            
                break;
            case 5:
                m_portfolio.saveData();
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
    tradeInputData.m_TradeClosed = false;
    
    m_portfolio.addTrade(tradeInputData);
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