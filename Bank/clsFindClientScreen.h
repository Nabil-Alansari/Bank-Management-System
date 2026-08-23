#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;

class clsFindClientScreen : protected clsScreen
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
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n---------------------------------";
		cout << endl;
	}

public:

	static void ShowFindClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pFindClient)) {

			return;
		}

		clsScreen::_DrawScreenHeader("\t  Find Client Screen");


		string AccountNumber;

		cout << "\n\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nAccount number is not found , chose another one: ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		if (!Client.IsEmpty()) {

			cout << "\nClient Found :-)\n";
		}
		else {

			cout << "\nClient Was not Found :-(\n";
		}

		_PrintClient(Client);

	}
};

