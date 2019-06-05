#include"account_bingqing.h"

double Account::cashBalance = 10000;

Account::Account(){}

double Account::getBalance()
{
	return cashBalance;
}

void Account::setBalance(double newbalance)
{
	cashBalance= newbalance;
}

void Account::depositCash(double add) {
	cashBalance += add;
}
void Account::withdrawalCash(double sub) {
	cashBalance -= sub;
}

string Account::getDateTime() {
	time_t seconds;
	seconds = time(NULL);
	tm * timeinfo;
	timeinfo = localtime(&seconds);
	//cout << "The current local time and date is:" << asctime(timeinfo);
	stringstream date;
	date << timeinfo->tm_mday
		<< "/" << 1 + timeinfo->tm_mon
		<< "/" << 1900 + timeinfo->tm_year
		<< " " << 1 + timeinfo->tm_hour << ":" << 1 + timeinfo->tm_min << ":" << 1 + timeinfo->tm_sec;
	string datetime = date.str();
	return datetime;
}