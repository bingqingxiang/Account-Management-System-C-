#ifndef _STOCKACCOUNT_H_
#define _STOCKACCOUNT_H_
#pragma warning(disable : 4996)
#include"account_bingqing.h"
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip> // setw()
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <time.h>

#include<cstdlib>
#include <cstdio>
#include<cstring>
#include"engine.h"

using namespace std;


class SotckAccount :public Account
{
public:
	SotckAccount();
	~SotckAccount();
	void Sinitial();
	void constructLL();
	bool initShares(string, int);
	void readResultTxt();
	void printResultTxt();
	
	bool isExist(string);
	bool sortList();
	int getRandomPriceIdx(string);
	double getTotal();
	//string getDateTime();

	void DisplayPriceForStock(string);
	void DisplayPortfolio();
	bool BuyShares(string,int,double);
	bool SellShares(string, int, double);
	void viewSTransactionHis();
	void PortfolioToTXT();
	void Graph();

	vector<string> name;
	vector<double> stockprice;
	vector<string> dateFromResult;

	vector<string> existSybl;
	vector<int> existNum;
	vector<double> existPrice;
	vector<double> existTotal;


private:
	struct Node {
		string StockSymbol;
		double price;
		int number; // number of stock
		double TotalValueForOne;

		struct Node* next;
		struct Node* prev;
	};

	int size;
	Node *head;
	double Total;

};


#endif // !_STOCKACCOUNT_H_
