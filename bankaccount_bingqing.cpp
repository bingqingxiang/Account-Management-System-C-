#include"bankaccount_bingqing.h"

BankAccount::BankAccount()
{
}

BankAccount::~BankAccount()
{
}

void BankAccount::ViewBalance() {
	cout << "\nCash Balance= $" << getBalance()<<endl;
}
bool BankAccount::DepositMoney(double add) {
	depositCash(add);
	ofstream fileBT;// BANK transaction history
	fileBT.open("bank__transaction_history.txt", fstream::app);
	fileBT << "Deposit   \t" << add << "\t" << getDateTime() << std::setw(15) << getBalance() << "\n";
	fileBT.close();
	return true;
}
bool BankAccount::WithdrawMoney(double sub) {
	if (sub <= getBalance()) {
		withdrawalCash(sub);
		ofstream fileBT;// BANK transaction history
		fileBT.open("bank__transaction_history.txt", fstream::app);
		fileBT << "Withdrawl\t" << sub << "\t" << getDateTime() << std::setw(15) << getBalance() << "\n";
		fileBT.close();
		return true;
	}
	else {
		cout << "bank accout do not have enough money";
		return false;
	}
	
}

void BankAccount::viewBTransactionHis() {
	string line;
	ifstream myfile("bank__transaction_history.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		myfile.close();
	}

	else cout << "Unable to open file(file does not exist)";
}