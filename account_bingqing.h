#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#pragma warning(disable : 4996)
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
class Account
{
public:
	Account();
	double getBalance();
	void setBalance(double);
	void depositCash(double);
	void withdrawalCash(double);
	string getDateTime();

private:
	static double cashBalance;

};

#endif //_ACCOUNT_H_
