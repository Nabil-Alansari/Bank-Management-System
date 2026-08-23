#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

class clsClientListScreen : protected clsScreen
{
private:

	static void _PrintClientRecordLine(clsBankClient Client) {

		cout << setw(8) << left << "" << "| " << setw(15) << left << Client.GetAccountNumber();
		cout << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.GetPhone();
		cout << "| " << setw(20) << left << Client.GetEmail();
		cout << "| " << setw(10) << left << Client.GetPinCode();
		cout << "| " << left << Client.GetAccountBalance() << " SR";


	}

public:

	static void ShowClientsList() {


		if (!CheckAccessRights(clsUser::enPermissions::pListClient)) {

			return;
		}

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "\t  Client List Screen";
		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client (s).";

		clsScreen::_DrawScreenHeader(Title, SubTitle);

	    cout <<setw(8) << left << "" << "\n\t-----------------------------------------------------------------";
		cout << "-------------------------------------\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin code";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------------";
		cout << "-------------------------------------\n" << endl;

		if (vClients.size() == 0) {

			cout << "\t\t\t\tNo Clients Available In the System!\n";
		}
		else {

			for (clsBankClient Client : vClients) {

				_PrintClientRecordLine(Client);
				cout << endl;

			}

		}

		cout << setw(8) << left << "\n\t-----------------------------------------------------------------";
		cout << "-------------------------------------\n" << endl;

	}


};

