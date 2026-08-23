#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

class clsWithdrawScreen : protected clsScreen
{
private:

	static void _PrintClient(clsBankClient Client) {

		cout << "\nClient Card:";
		cout << "\n---------------------------------";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFullName    : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.GetAccountNumber();
		cout << "\nPassword    : " << "*************";
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n---------------------------------";
		cout << endl;
	}
	
public :

	static void ShowWithdrawScreen() {

		_DrawScreenHeader("\t  Withdraw Screen");

		string AccountNumber;

		cout << "\n\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nAccount number is not found , chose another one: ";
			AccountNumber = clsInputValidate<string>::ReadString();

		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		double Amount;

		cout << "\nPlease enter withdraw amount ? ";
		Amount = clsInputValidate<double>::ReadNumber();


		cout << "\nAre you sure want to preform this transaction ? y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {

			
			if (Client.Withdraw(Amount)) {
				cout << "\nAmount withdraw Successfully.\n";
				cout << "\nNew Balance Is: " << Client.AccountBalance;
			}
			else {
				
				cout << "\nCannot withdrae, insuffecient Balance!\n";
				cout << "\nAmount to withdraw is: " << Amount;
				cout << "\nYour Balance Is: " << Client.AccountBalance;
			}
		}
		else {

			cout << "\nOpreation was cancelled.\n";
		}
	}
};

