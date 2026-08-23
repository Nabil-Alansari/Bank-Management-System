#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsListUsers : protected clsScreen
{
private:

	static void _PrintUserRecordLine(clsUser User) {

		cout << setw(8) << left << "" << "| " << setw(15) << left << User.GetUserName();
		cout << "| " << setw(20) << left << User.FullName();
		cout << "| " << setw(12) << left << User.GetPhone();
		cout << "| " << setw(20) << left << User.GetEmail();
		cout << "| " << setw(16) << left << User.GetPassword();
		cout << "| " << setw(6) << left << User.GetPermissions();
	}

public:

	static void ShowListUsersScreen() {

		vector <clsUser> vUsers = clsUser::GetListUsers();

		string Title = "\t  User List Screen";
		string Subtitle = "\t    (" + to_string(vUsers.size()) + ") User (s).";

		clsScreen::_DrawScreenHeader(Title, Subtitle);

		cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------------";
		cout << "-------------------------------------------\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(15) << "User Name";
		cout << "| " << left << setw(20) << "Full Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(16) << "Password";
		cout << "| " << left << setw(6) << "Permissions";
		cout << setw(8) << left << "" << "\n\t-----------------------------------------------------------------";
		cout << "-------------------------------------------\n" << endl;

		if (vUsers.size() == 0) {

			cout << "\t\t\t\t\tNo User available in the system!\n";
		}
		else {

			for (clsUser User : vUsers) {

				_PrintUserRecordLine(User);
				cout << endl;

			}

		}

		cout << setw(8) << left << "\n\t-----------------------------------------------------------------";
		cout << "-------------------------------------------\n" << endl;

	}


};

