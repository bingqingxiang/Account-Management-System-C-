// Name: Bingqing Xiang
// Course: 16:332:503, Programming Finance
// Final Project
// Due:05/09/2019
#pragma warning(disable : 4996)
#include"account_bingqing.h"
#include"stockaccount_bingqing.h"
#include"bankaccount_bingqing.h"

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

using namespace std;


int main() {

	SotckAccount s1;
	BankAccount b1;

	string path1 = "stock_transaction_history.txt";
	ifstream fin(path1);
	if (! fin.is_open()) {

	ofstream fileST;// STOCK transaction history
	fileST.open("stock_transaction_history.txt", fstream::app);
	fileST << "Event \t CompSymbol \tNumber \tPricePerShare \t TotalValue \t Time\n";
	fileST.close();
	
	ofstream fileBT;// BANK transaction history
	fileBT.open("bank__transaction_history.txt", fstream::app);
	fileBT << "Event \t        Amount\tDate \t time \t       Balance\n";
	fileBT.close();

	

	}
	else {// initialize when have previous result
		s1.Sinitial();
		
	}


	ofstream fileTotal;// total protfolio value trend
	fileTotal.open("total_portfolio_trend.txt", fstream::app);
	fileTotal.close();


	
	while(true){
		int choice;
	    cout << "\nWelcome to the Account Management System." << endl ;
		cout << "Please select an account to access: " << endl;
		cout << "1. Stock Portfolio Account" << endl;
		cout << "2. Bank Account" << endl;
		cout << "3. Exit" << endl;
		cout << "Option: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			int subchoice = { 0 };
			bool subloop = true;
			
			do {
            cout << "\nStock Portfolio Account" << endl;
			cout << "Please select an option :" << endl;
			cout << "1. Display the price for a stock symbol" << endl;
			cout << "2. Display the current portfolio" << endl;
			cout << "3. Buy shares" << endl;
			cout << "4. Sell shares" << endl;
			cout << "5. View a graph for the portfolio value" << endl;
			cout << "6. View transaction history" << endl;
			cout << "7. Return to previous menu" << endl;
			cout << "Option: ";
			cin >> subchoice;

			switch (subchoice) {
			case 1:
			{
				string userSymbol;
				cout << "\nEnter Company-Symbol: ";
				cin.ignore();
				getline(cin, userSymbol);
				s1.DisplayPriceForStock(userSymbol);
			}
				break;
			case 2:
			{
				cout << "\nDisplay the current portfolio" << endl;
				s1.DisplayPortfolio();
			}
				break;
			case 3:
			{
				cout << "\nBuy shares" << endl;
				string userSymbol;
				int amoutToBuy;
				double maxLimit = { 0.0 };
				cout << "Enter Company-Symbol: ";
				cin.ignore();
				getline(cin, userSymbol);
				cout << "Amount of shares to buy: ";
				cin >> amoutToBuy;
				cout << "Maximum price limit:";
				cin >> maxLimit;

				bool successBuy;
				successBuy=s1.BuyShares(userSymbol,amoutToBuy,maxLimit);
				if (!successBuy) {
					cout << "The purchase fail" << endl;
				}
				else {
					cout << "The purchase succeed" << endl;
				}
			}
				break;
			case 4:
			{
				cout << "\nSell shares" << endl;
				string userSymbol;
				int amoutToSell;
				double minLimit = { 0.0 };
				cout << "Enter Company-Symbol: ";
				cin.ignore();
				getline(cin, userSymbol);
				cout << "Amount of shares to sell: ";
				cin >> amoutToSell;
				cout << "Minimum price limit:";
				cin >> minLimit;

				bool successSell;
				successSell = s1.SellShares(userSymbol, amoutToSell, minLimit);
				if (!successSell) {
					cout << "The sell fail" << endl;
				}
				else {
					cout << "The sell succeed" << endl;
				}
			}
				break;
			case 5:
			{
				s1.Graph();
			}
				break;
			case 6: {
				s1.viewSTransactionHis();
			}
				break;
			case 7:
				subloop = false;
				break;
			default:
				cout << "invalid option for Stock Portfolio Account"<<endl;
				break;
			}
			} while (subloop);
			
		}
			break;
		case 2:
		{
			int subchoice = { 0 };
			bool subloop = true;

			do {
				cout << "\nStock Portfolio Account" << endl;
				cout << "Please select an option :" << endl;
				cout << "1. View account balance" << endl;
				cout << "2. Deposit Money" << endl;
				cout << "3. Withdraw Money" << endl;
				cout << "4. Print out history" << endl;
				cout << "5. Return to previous menu" << endl;
				cout << "Option: ";
				cin >> subchoice;
				switch (subchoice)
				{
				case 1: {
					b1.ViewBalance();
				}
					break;
				case 2:
				{
					double addmoney;
					cout << "Enter the amount money to deposit: $";
					cin >> addmoney;
					b1.DepositMoney(addmoney);
				}
					break;
				case 3: {
					double submoney;
					cout << "Enter the amount money to withdraw: $";
					cin >> submoney;
					bool succw=b1.WithdrawMoney(submoney);
					if (!succw) {
						cout << "fail to withdraw" << endl;
					}
				}
					break;
				case 4: {
					b1.viewBTransactionHis(); 
				}
					break;
				case 5:
					subloop = false;
					break;
				default:
					cout << "invalid choice for bank account" << endl;
					break;
				}
			} while (subloop);
			
		}
			break;
		case 3:
		{
			s1.PortfolioToTXT();

			ofstream fileTotal;// total protfolio value trend
			fileTotal.open("total_portfolio_trend.txt", fstream::app);
			fileTotal << s1.getTotal() <<"\t\t"<<s1.getDateTime()<<endl;
			fileTotal.close();
			return 0;
		}
			
			break;
		default:
			break;
		}
		
	} 
	


	

	system("pause");
	return 0;
}