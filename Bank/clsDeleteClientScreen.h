#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
 
using namespace std;

class clsDeleteClientScreen : protected clsScreen
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
		cout << "\nPassword    : " << "***************";
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n---------------------------------";
		cout << endl;
	}

public:

	static void ShowDeleteClientScreen() {


		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {

			return;
		}

		_DrawScreenHeader("\tDelete Client Screen");

		string AccountNumber;


		cout << "\n\nPlease Enter Account Number: ";

		AccountNumber = clsInputValidate<string>::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nAccount number is not found , chose another one: ";
			AccountNumber = clsInputValidate<string>::ReadString();


		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		cout << "Are you sure you want delete this client y/n? ";

		char Answer = 'n';

		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {

			if (Client.Delete()) {


				cout << "\nClient Deleted Successfully :-)\n";
				_PrintClient(Client);


			}
			else {

				cout << "\nError Client was not Deleted\n";

			}
		}
	}
};

