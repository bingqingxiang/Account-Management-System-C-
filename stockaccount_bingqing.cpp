#include"stockaccount_bingqing.h"

SotckAccount::SotckAccount():Account(){
	readResultTxt();
	head = NULL;
	size = 0;
}

SotckAccount::~SotckAccount() {
	Node *current = head;
	
	while (current != NULL) {
		Node *temp = NULL;
		temp = current;
		current = current->next;
		delete temp;
	}
}

void SotckAccount::Sinitial() {
	string line;
	ifstream file0("stock_portfolit.txt");
	int firstline = 0;
	if (file0.is_open())
	{
		while (getline(file0, line))
		{
			istringstream iss(line);

			int i = 0;
			for (string s; iss >> s;)
			{
				if (firstline == 0) {//get the first line for cash balance
					setBalance(stod(s));
					firstline = 1;
				}
				else {
					if (i == 0) {
						existSybl.push_back(s);
						i++;
					}
					else if (i == 1)
					{
						existNum.push_back(stoi(s));
						i++;
					}
					else if(i==2){
						existPrice.push_back(stod(s));
						i++;
					}
					else {
						existTotal.push_back(stod(s));

					}
				}
				
			}
		}
	}
	constructLL();// construct the linked list by the previous result
}
void SotckAccount::constructLL() {
	size = static_cast<int>(existSybl.size());
	for (int i = 0; i < size; i++) {
		initShares(existSybl[i], existNum[i]);
	}
	sortList();
}

bool SotckAccount::initShares(string sybl, int num) {
		Node *add = new Node;// create a new entry
		int index = getRandomPriceIdx(sybl);
		add->StockSymbol = sybl;
		add->price = stockprice[index];
		add->number = num;
		add->TotalValueForOne = stockprice[index] * num;

		if (head == NULL) {// if the list is empety
			head = add;
			add->prev = NULL;
			add->next = NULL;
		}
		else
		{
			Node *current = head;
			if (head->TotalValueForOne < add->TotalValueForOne)// if the head have smaller value than the new node
			{
				add->next = head;
				add->prev = NULL;
				head = add;
			}
			else
			{
				bool insertSucceed = false;
				while (current != NULL && (!insertSucceed))
				{
					if ((current->TotalValueForOne > add->TotalValueForOne) && ((current->next) != NULL))//proceed to next node
					{
						current = current->next;
					}
					else if ((current->TotalValueForOne > add->TotalValueForOne) && ((current->next) == NULL))// insert at the end of the list
					{
						current->next = add;
						add->prev = current;
						add->next = NULL;
						insertSucceed = true;

					}
					else// insert in the middle of the list
					{
						Node *temp = current->prev;
						temp->next = add;
						current->prev = add;
						add->next = current;
						add->prev = temp;
						insertSucceed = true;
					}
				}

			}


		}
		return true;

}

	


bool SotckAccount::isExist(string sybl) {
	if (head == NULL)
		return false;
	Node *current = head;
	bool exist = false;
	while (current != NULL && !exist)
	{
		if (current->StockSymbol == sybl)
		{
			exist = true;
		} 
		else
		{
			current = current->next;
		}
			
	}
	return exist;
}

bool SotckAccount::sortList() {
	bool isSort=false;
	if (head == NULL)//if the list is empety it is sorted
	{
		isSort = true;
		
	}
	else 
	{
	bool swapped = false;
	
	do{
		swapped = false;
		Node *current = head;
		while (current->next != NULL)
		{
			if ((current->TotalValueForOne) < (current->next->TotalValueForOne))
			{
				swap(current->StockSymbol, current->next->StockSymbol);
				swap(current->price, current->next->price);
				swap(current->number, current->next->number);
				swap(current->TotalValueForOne,current->next->TotalValueForOne);
				swapped = true;
			}
			current = current->next;
		}

	} while (swapped);
	isSort = true;
	}
	return isSort;
}

int SotckAccount::getRandomPriceIdx(string sybl) {
	srand((unsigned)time(0));// make sure rand generate rand value 
	int ran = (rand() % 2) + 1;// random numbe 0 or 1
	int searchLength = static_cast<int>(name.size())/ ran;
	int index = -1;
	for (int i = 0; i < searchLength; i++) {
		if (name[i] == sybl) {
			index = i;
		}
	}
	
	return index;
	
}

double SotckAccount::getTotal() {
	Node *current = head;
	double sumTotal = { 0.0 };
	while (current != NULL)
	{
		sumTotal += current->TotalValueForOne;
		current = current->next;
	}
	Total = sumTotal+getBalance();
	return Total;
}

/*
string SotckAccount::getDateTime() {
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
*/

void SotckAccount::readResultTxt() {
	string line;
	ifstream file1("Result_1.txt");
	if (file1.is_open())
	{
	while (getline(file1, line))
	{
		
		//cout << line.substr(0,4)  <<endl;
		istringstream iss(line);
		int i = 0;
		for (string s; iss >> s;)
		{
			if (i == 0) {
				name.push_back(s);
				i++;
			}
			else if (i==1)
			{
				stockprice.push_back(stod(s));
				i++;
				
			}
			else {
				dateFromResult.push_back(s);
			}
			
		}
	}
	file1.close();
	}

	ifstream file2("Result_2.txt");
	if (file2.is_open())
	{
		while (getline(file2, line))
		{
			istringstream iss(line);
			int i = 0;
			for (string s; iss >> s;)
			{
				if (i == 0) {
					name.push_back(s);
					i++;
				}
				else if (i == 1)
				{
					stockprice.push_back(stod(s));
					i++;

				}
				else {
					dateFromResult.push_back(s);
				}

			}
		}
		file2.close();
	}
	
}

void SotckAccount::printResultTxt() {
	int length = static_cast<int>(name.size());
	//cout << name.size() << stockprice.size() << date.size();
	cout << "Stock price list"<<endl;
	for (int i = 0; i < length; i++) {
		cout << name[i]<<"\t"<< stockprice[i]<<"\t"<< dateFromResult[i]<<endl;
	}
	


}

void SotckAccount::DisplayPriceForStock(string sybl) {
	
	srand((unsigned)time(0));// make sure rand generate rand value 
	int ran = (rand() % 2) + 1;// random numbe 0 or 1
	int searchLength = static_cast<int>(name.size()) / ran;
	int index = -1;
	for (int i = 0; i < searchLength; i++) {
		if (name[i] == sybl) {
			index = i;
		}
	}

	if (index == -1) {
		cout << "Company-Symbol" << "\t" << "Price Per Share" << endl;
		cout << sybl << "\t         " << "Stock Not Found" << endl;
	}
	else {
	cout << "Company-Symbol"<<"\t"<<"Price Per Share" << endl;
	cout << sybl<<"\t         "<< stockprice[index]<<endl;
	}
	
}

void SotckAccount::DisplayPortfolio() {
	if (head == NULL) {
		cout<<"Cash balance = "<<Account::getBalance()<<endl;
		cout << "The stock portfolio is empety" << endl;
	}
	else {
		Node *current = head;// first loop to get the current price for all node
		while (current != NULL) {
			string sybl = current->StockSymbol;
			current->price = stockprice[getRandomPriceIdx(sybl)];
			current->TotalValueForOne = (current->price)*current->number;
			current = current->next;
		}

		//if (sortList()) // sort the linked list before print
		//{
		//	cout << "sort successful";
		//}
		sortList();

		cout << "Cash balance = $" << Account::getBalance() << endl;
		cout << "CompanySymbol\t Number\t PricePerShare\t TotalValue" << endl;
		Node *current0 = head;// print the printed list
		while (current0 != NULL) {
			cout << current0->StockSymbol << "\t           " << current0->number << "\t      " << current0->price << "\t    " << current0->TotalValueForOne << endl;
			current0 = current0->next;
		}
		cout << "Total protfolio value: $"<<getTotal();
	}
}

bool SotckAccount::BuyShares(string sybl,int num,double maxlimit) {

	srand((unsigned)time(0));// make sure rand generate rand value 
	int ran = (rand() % 2) + 1;// random numbe 0 or 1
	int searchLength = static_cast<int>(name.size()) / ran;
	int index = -1;// if stock not found
	for (int i = 0; i < searchLength; i++) {
		if (name[i] == sybl) {
			index = i;
		}
	}

	if (index == -1)// first check if the symbol in the stock market 
	{
		cout << sybl << "\t" << "Stock ticker Not Found";
		return false;
	}
	else if (stockprice[index] > maxlimit) {// if the price reaches the maximum limit
		cout << "the price of the stock " << sybl << " exceed the maximum limit " << maxlimit;
		return false;
	}
	else if ((stockprice[index]*num)>getBalance()) {
		cout << "Not enough money in the Bank" << endl;
		return false;
	}
	else {
		size++;

		withdrawalCash(stockprice[index] * num);// withdrawal money from bank account

		ofstream fileST;// STOCK transaction history
		fileST.open("stock_transaction_history.txt", fstream::app);
		fileST << "BUY\t  "<<sybl<<"    \t"<<num << "   \t" << stockprice[index] <<  std::setw(17) << stockprice[index] * num << "     \t" << getDateTime()<<"\n";
		fileST.close();

		ofstream fileBT;// BANK transaction history
		fileBT.open("bank__transaction_history.txt", fstream::app);
		fileBT << "Withdrawl\t"<< stockprice[index] * num << "\t" << getDateTime() << std::setw(15) << getBalance()<<"\n";
		fileBT.close();

		if (isExist(sybl)) // if we already have the symbol in the protfolio
		{
		 Node *current0 = head;
			while (current0 != NULL)
			{
				if (current0->StockSymbol == sybl)
				{
					current0->price = stockprice[index];
					current0->number += num;
					current0->TotalValueForOne = (current0->number)*(current0 -> price);
					break;
				}
				else
				{
					current0 = current0->next;// search the next one
				}

			}
			sortList();
			return true;
		} 
		else// if the new stock is not on our list add a new node
		{
				Node *add = new Node;// create a new entry
				add->StockSymbol = sybl;
				add->price = stockprice[index];
				add->number = num;
				add->TotalValueForOne = stockprice[index] * num;

				if (head == NULL) {// if the list is empety
					head = add;
					add->prev = NULL;
					add->next = NULL;
				}
				else
				{
					Node *current = head;
					if (head->TotalValueForOne < add->TotalValueForOne)// if the head have smaller value than the new node
					{
						add->next = head;
						add->prev = NULL;
						head = add;
					}
					else
					{
						bool insertSucceed = false;
						while (current != NULL && (!insertSucceed))
						{
							if ((current->TotalValueForOne > add->TotalValueForOne) && ((current->next) != NULL))//proceed to next node
							{
								current = current->next;
							}
							else if ((current->TotalValueForOne > add->TotalValueForOne) && ((current->next) == NULL))// insert at the end of the list
							{
								current->next = add;
								add->prev = current;
								add->next = NULL;
								insertSucceed = true;

							}
							else// insert in the middle of the list
							{
								Node *temp = current->prev;
								temp->next = add;
								current->prev = add;
								add->next = current;
								add->prev = temp;
								insertSucceed = true;
							}
						}

					}

					
				}
				return true;
			
		}
	}
}

bool SotckAccount::SellShares(string sybl, int num, double minlimit) {
	if (!isExist(sybl)) {// if u do not have the stock
		cout << "Stock is not in the current portfolio" << endl;
		return false;
	}
	else {
		Node *current = head;
		while ((current != NULL) && (current->StockSymbol != sybl))
		{
			current = current->next;// search the next one
		}

		current->price = stockprice[getRandomPriceIdx(sybl)];// find the price for the stock

		if (num > (current->number)) {// check if hold enough stock
			cout <<sybl<< " do not have enough number of stock"<<endl;
			return false;
		}
		else if (current->price < minlimit) {// check if of with min limit
			cout << "the price of the stock " << sybl << " less than the minimum limit " << minlimit;
			return false;
		}
		else if (num == (current->number)) 
		{//if delete the stock need to delete the node

			depositCash((current->price)*num);

			ofstream fileST;// STOCK transaction history
			fileST.open("stock_transaction_history.txt", fstream::app);
			fileST << "SELL\t  " << sybl << "    \t" << num << "   \t" << current->price << std::setw(17) << current->price * num << "     \t" << getDateTime() << "\n";
			fileST.close();

			ofstream fileBT;// BANK transaction history
			fileBT.open("bank__transaction_history.txt", fstream::app);
			fileBT << "Deposit   \t" << current->price * num << "\t" << getDateTime() << std::setw(15) << getBalance() << "\n";
			fileBT.close();

			if (head == current)
				head = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			if (current->prev != NULL)
				current->prev->next = current->next;
			//cout << "test" << current->next->price << "\t" << current->prev->price << endl;
			delete current;
			
			return true;
		}
		else {

			depositCash((current->price)*num);

			ofstream fileST;// STOCK transaction history
			fileST.open("stock_transaction_history.txt", fstream::app);
			fileST << "SELL \t " << sybl << "    \t" << num << "   \t" << current->price << std::setw(17) << current->price * num << "     \t" << getDateTime() << "\n";
			fileST.close();

			ofstream fileBT;// BANK transaction history
			fileBT.open("bank__transaction_history.txt", fstream::app);
			fileBT << "Deposit   \t" << current->price * num << "\t" << getDateTime() << std::setw(15) << getBalance() << "\n";
			fileBT.close();

			current->number -= num;
			current->TotalValueForOne = (current->number)*(current->price);
			sortList();
			return true;
		}

	}

}

void SotckAccount::viewSTransactionHis() {
	string line;
	ifstream myfile("stock_transaction_history.txt");
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

void SotckAccount::PortfolioToTXT() {
	ofstream sfile;
	sfile.open("stock_portfolit.txt");
	
	if (head == NULL) {
		sfile << "Cash balance = " << Account::getBalance() << endl;
		//sfile << "The stock portfolio is empety" << endl;
	}
	else {
		Node *current = head;// first loop to get the current price for all node
		while (current != NULL) {
			string sybl = current->StockSymbol;
			current->price = stockprice[getRandomPriceIdx(sybl)];
			current->TotalValueForOne = (current->price)*current->number;
			current = current->next;
		}

		//if (sortList()) // sort the linked list before print
		//{
			//sfile << "sort successful";
		//}
		sortList();

		//sfile << "Cash balance = $" << Account::getBalance() << endl;
		//sfile << "CompanySymbol\t Number\t PricePerShare\t TotalValue" << endl;
		sfile << Account::getBalance() << endl;

		Node *current0 = head;// print the printed list
		while (current0 != NULL) {
			sfile << current0->StockSymbol << "\t           " << current0->number << "\t      " << current0->price << "\t    " << current0->TotalValueForOne << endl;
			current0 = current0->next;
		}
		//sfile << "Total protfolio value: $" << getTotal();
	}
	sfile.close();
}

void SotckAccount::Graph() {
	string line;
	ifstream file1("total_portfolio_trend.txt");
	vector<double> v;
	if (file1.is_open())
	{
		while (getline(file1, line))
		{
			//cout << line.substr(0,4)  <<endl;
			istringstream iss(line);
			int i = 0;
			for (string s; iss >> s;)
			{
				if (i == 0) {
					v.push_back(stod(s));
					i++;
				}
			}
		}
	}

	int l = static_cast<int>(v.size());//length of the portfolit
	double *arry = NULL;
	double *arrx = NULL;
	arry = new double[l];
	arrx = new double[l];
	for (int i = 0; i < l;i++) {
		arry[i] = v[i];
		arrx[i] = i;
	}
    // use matlab to plot

	const int BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];
	
	Engine* ep;
	mxArray *x1 = NULL;
	mxArray *y1 = NULL;
	if ((ep = engOpen("")) == NULL)
	{
		printf("Engine Fail\n");
	}
	engOutputBuffer(ep, buffer, BUFFER_SIZE);
	printf("Init Success\n");

	//double x[5] = { 1.0, 2.5,3.7,4.4,5.1 }; // for testing
	//double y[5] = { 3.3,4.7,9.6,15.6,21.3 };
	x1 = mxCreateDoubleMatrix(1, l, mxREAL);
	y1 = mxCreateDoubleMatrix(1, l, mxREAL);

	memcpy((char*)mxGetPr(x1), (void *)arrx, l * sizeof(double));
	memcpy((char*)mxGetPr(y1), (void *)arry, l * sizeof(double));

	engPutVariable(ep, "x", x1);
	engPutVariable(ep, "y", y1);
	engEvalString(ep, "plot(x,y)");
	getchar();
	system("pause");
	engClose(ep);


	delete[] arrx;
	delete[] arry;
}