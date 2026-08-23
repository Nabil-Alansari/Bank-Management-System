#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
using namespace std;


class clsUpdateClientScreen : protected clsScreen
{
private :

	
	static void _PrintClient(clsBankClient Client) {

		cout << "\nClient Card:";
		cout << "\n---------------------------------";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFullName    : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.GetAccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n---------------------------------";
		cout << endl;
	}

	static 	void _ReadClientInfo(clsBankClient& Client) {

		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate<string>::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate<string>::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate<string>::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate<string>::ReadString();


		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate<string>::ReadString();

		cout << "\nEnter Balance: ";
		Client.AccountBalance = clsInputValidate<float>::ReadNumber();


	}

public:

	static void ShowUpdateClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClient)) {

			return;
		}

		clsScreen::_DrawScreenHeader("\t   Update Client Screen");

		string AccountNumber;

		cout << "\n\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nAccount number is not found , chose another one: ";
			AccountNumber = clsInputValidate<string>::ReadString();

		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		cout << "\n\nUpdate Client Info:";
		cout << "\n--------------------\n";
		_ReadClientInfo(Client);

		clsBankClient::enSaveResult SaveResult;

		SaveResult = Client.Save();

		switch (SaveResult) {

		case clsBankClient::enSaveResult::scSucceeded:

			cout << "\nAccount Update Successfully :-)\n";
			break;

		case clsBankClient::enSaveResult::svFalidEmptyObject:

			cout << "\nError account was not save because it's Empty\n";
			break;
		}
	}

};

