#include "TradeInputHandler.h"
#include "TradingConstants.h"
#include "TradePrinter.h"
#include "Portfolio.h"
#include <iostream>
#include <optional>

#include "ITradeRepository.h"

void TradeInputHandler::run() {
    bool isRunning = true;
    
    while (isRunning) {
        clearConsole();
        std::cout << "[1] Create trades" << std::endl;
        std::cout << "[2] Show trades" << std::endl;
        std::cout << "[3] Show calculation" << std::endl;
        std::cout << "[4] Load data" << std::endl;
        std::cout << "[5] Save data" << std::endl;
        std::cout << "[6] End" << std::endl;
        
        int inputMenuIndex = readSaveInteger(6);
        if (inputMenuIndex == 0)
            continue;
        
        clearConsole();
        switch (inputMenuIndex)
        {
            case 1:
            getTradeInputData();
            break;
            
            case 2:
            changeDataInTrade();
            break;
            
            case 3:
                {
                    std::string input;
                    long long totalGrossWin = m_portfolio.calculateTotalGrossWin();
                    long long totalNetWin = m_portfolio.calculateTotalNetWin();
                    long long totalFee = m_portfolio.calculateTotalFee();
                    long long totalTax = m_portfolio.calculateTotalTax();
                    
                    
                    displayPerformanceReport(totalGrossWin, totalFee, totalTax, totalNetWin);
                    std::cout << std::endl << "Press enter to continue";
                    std::getline(std::cin, input);
                    break;
                }
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
    
    if (auto StockName = readString("Set stock name: "))
    {
        tradeInputData.m_StockName = *StockName;
    }
    else
    {
        return;
    }
    
    if (auto StockAmount = readLongLong("Set stock amount: "))
    {
        tradeInputData.m_StockAmount = *StockAmount;
    }
    else
    {
        return;
    }
    
    if (auto SingleBuyPrice = readLongLong("Set single buy price: "))
    {
        tradeInputData.m_SingleBuyPrice = *SingleBuyPrice;
    }
    else
    {
        return;
    }
    
    if (auto BuyFee = readLongLong("Set fee: "))
    {
        tradeInputData.m_BuyFee = *BuyFee;
    }
    else
    {
        return;
    }
    
    if (auto BuyDate = readDate("Set buy date YYYY-MM-DD: "))
    {
        tradeInputData.m_BuyDate = *BuyDate;
    }
    else
    {
        return;
    }
    
    tradeInputData.m_TradeClosed = false;
    
    m_portfolio.addTrade(tradeInputData);
}
void TradeInputHandler::displayPerformanceReport(long long totalGrossWin, long long totalFee, long long totalTax, long long totalNetWin)
{
    std::cout << "Total Gross Win : " << std::setw(30 - 18) << std::fixed << std::setprecision(2) << std::right << Trading::longlongToDisplay(totalGrossWin) << std::endl;
    std::cout << "Total Fee: " << std::setw(30 - 11) << std::fixed << std::setprecision(2) << std::right << Trading::longlongToDisplay(totalFee) << std::endl;
    std::cout << "Total Tax: " << std::setw(30 - 11) << std::fixed << std::setprecision(2) << std::right << Trading::longlongToDisplay(totalTax) << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "Total Net Win: " << std::setw(30 - 15) << std::fixed << std::setprecision(2) << std::right << Trading::longlongToDisplay(totalNetWin) << std::endl;
}
std::optional<long long> TradeInputHandler::readLongLong(const std::string &command)
{
    std::string inputData;
    std::cout << command;
    
    while (true)
    {
        std::getline(std::cin, inputData);

        try
        {            
            long long Data = static_cast<long long>(std::round(std::stod(inputData) * Trading::SCALE));
            
            if (Data <= 0)
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
            if (inputData.empty())
            {
                return std::nullopt;
            }
            else
            {
                std::cout << "Only numbers are valid" << std::endl;
            }
        }
    }
}
std::optional<std::string> TradeInputHandler::readString(const std::string &command)
{
    std::string inputData;
    std::cout << command;
    
    while (true)
    {
        std::getline(std::cin, inputData);
        if (inputData.empty())
        {
            return std::nullopt;
        }
        else return inputData;
    }
}
std::optional<std::chrono::year_month_day> TradeInputHandler::readDate(const std::string &command)
{
    std::string inputString;
    std::chrono::year_month_day inputYear;
    
    while (true)
    {
        std::cout << command;
        
        std::getline(std::cin, inputString);
        std::istringstream ss{inputString};

        if (ss >> std::chrono::parse("%F", inputYear) && inputYear.ok()) {
            return inputYear;
        } else {
            if (inputString.empty())
            {
                return std::nullopt;
            }
            else
            {
                std::cout << "Ungültiges Datum oder falsches Format. Bitte YYYY-MM-DD eingeben: ";
            }
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
    tradeData.tax = m_portfolio.getTrades()[indexTrade - 1].getTax();
    tradeData.singleSellPrice = m_portfolio.getTrades()[indexTrade - 1].getSingleSellPrice();
    tradeData.sellDate = m_portfolio.getTrades()[indexTrade - 1].getSellDate();
    
    std::cout << std::endl << "[1] Sell Fee";
    std::cout << std::endl << "[2] Single Sell Price";
    std::cout << std::endl << "[3] Sell Date";
    std::cout << std::endl << "[4] Tax";
    std::cout << std::endl << "Press valid field number to change or enter to leave: ";
      
    int indexField = readSaveInteger(4);
    if (indexField == 0)
        return;
    
    switch (indexField)
    {
    case 1:
        if (auto sellFee = readLongLong("Set fee or enter to leave: "))
        {
            tradeData.sellFee = *sellFee;
        }
        else
        {
            return;
        }
        break;
    case 2:
        if (auto singleSellPrice = readLongLong("Set single sell price or enter to leave: "))
        {
            tradeData.singleSellPrice = *singleSellPrice;
        }
        else
        {
            return;
        }
        break;
    case 3:
        {
            tradeData.sellDate = readDate("Set sell date YYYY-MM-DD or enter to leave: ");
            if (tradeData.sellDate.has_value())
            {
                std::chrono::sys_days sysSellDate {tradeData.sellDate.value()};
            }
            else
            {
                return;
            }
            break;
        }
    case 4:
        if (auto tax = readLongLong("Set tax or enter to leave: "))
        {
            tradeData.tax = *tax;
        }
        else
        {
            return;
        }
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
void TradeInputHandler::clearConsole() {
#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}