#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;


class clsAddNewClientScreen : protected clsScreen
{

private :

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
	
	static void ShowAddNewClientScreen() {


		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {

			return;
		}

		clsScreen::_DrawScreenHeader("\t   Add New Client Screen");


		string AccountNumber;

		cout << "\n\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nAccount Number Is Already Used, Choose another one: ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResult Save;

		Save = NewClient.Save();

		switch (Save) {

		case clsBankClient::enSaveResult::scSucceeded:

			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintClient(NewClient);
		
			break;

		case clsBankClient::enSaveResult::svFalidEmptyObject:

			cout << "\nError account was not save because it's Empty\n";
			break;

		case clsBankClient::enSaveResult::svFaildAccountNumberExists:

			cout << "\nAccount Number Is Already Used\n";
			break;
		}
	}

};

