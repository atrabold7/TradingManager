#pragma once

class Portfolio;
class Trade;

class TradePrinter
{
public:
	static void printTrade(int StockId, const Trade &trade) ;
	static void printAll(const Portfolio& m_portfolio);
};
