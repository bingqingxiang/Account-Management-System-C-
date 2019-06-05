#ifndef _BANKACCOUNT_H_
#define _BANKACCOUNT_H_

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

using namespace std;

class BankAccount :public Account
{
public:
	BankAccount();
	~BankAccount();
	void ViewBalance();
	bool DepositMoney(double add);
	bool WithdrawMoney(double sub);
	void viewBTransactionHis();
	


private:

};

#endif // !_BANKKACCOUNT_H_

