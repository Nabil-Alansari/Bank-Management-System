#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsTransferScreen : protected clsScreen
{
private:

	static void _PrintClientCard(clsBankClient Client) {


		cout << "\n\nClient Card:\n\n";
		cout << "-------------------------------\n\n";
		cout << "Full Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.GetAccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n\n-------------------------------\n\n";

	}

	static bool _IsDestiantion(string AccSource, string AccDestiantion) {

		return (AccSource == AccDestiantion) ? true : false;

	}

	static string _ReadAccountNumber(bool IsDestiantion = false , string AccSourceClient = "") {

		string AccNumber;
		bool CheckDestiantion = false;

		if (!IsDestiantion) 

	        cout << "\n\nPlease Enter Account Number To Transfer From: ";
		else 
			cout << "\n\nPlease Enter Account Number To Transfer To: ";

		AccNumber = clsInputValidate<string>::ReadString();

		if (IsDestiantion) {

			CheckDestiantion = _IsDestiantion(AccSourceClient, AccNumber);
		}

		while (!clsBankClient::IsClientExist(AccNumber) || CheckDestiantion) {

			if (CheckDestiantion) {

				cout << "\nYou cannot enter the same account number you want to transfer from , ";
				cout << "Choose another one: ";
			}
			else {

				cout << "\nAccount number is not found , chose another one: ";
			}

			AccNumber = clsInputValidate<string>::ReadString();
			CheckDestiantion = _IsDestiantion(AccSourceClient,AccNumber);
		}
		return AccNumber;

	}

	static double _ReadAmount(clsBankClient SourceClient) {


		cout << "\nEnter Transfer Amount? ";
		double Amount = clsInputValidate<double>::ReadNumber();

		while (Amount > SourceClient.AccountBalance) {

			cout << "\n\nAmount Exceeds th available Balance, Enter another amount: ";
			Amount = clsInputValidate<double>::ReadNumber();

		}

		return Amount;
	}

public:

	static void ShowTransferScreen() {

		_DrawScreenHeader("\t  Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());

		_PrintClientCard(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber(true , SourceClient.GetAccountNumber()));

		_PrintClientCard(DestinationClient);

		double Amount = _ReadAmount(SourceClient);


		char Answer = 'n';
		
		cout << "\nAre you sure want to perform this operation? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			if (SourceClient.Transfer(Amount , DestinationClient)) {

				cout << "\n\nTransfer done successfully\n";
				_PrintClientCard(SourceClient);
				_PrintClientCard(DestinationClient);

			}
			else {

				cout << "\n\nTransfer was not successful!\n";
			}

		}
	}

};

