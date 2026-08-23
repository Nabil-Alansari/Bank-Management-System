#pragma once
#include <iostream>
#include <fstream>
#include "clsString.h"
#include <iomanip>
#include "clsScreen.h"
class clsLogInRegisterScreen : protected clsScreen
{
private:

	static void _PrintRecordLogInRegister(clsUser::stLoginRegisterRecord LogInRegister) {

		cout << setw(8) << left << "" << " | " << setw(37) << left << LogInRegister.DateTime;
		cout << "| " << setw(23) << left << LogInRegister.Username;
		cout << "| " << setw(22) << left << LogInRegister.Password;
		cout << "| " << setw(20) << left << LogInRegister.Permissions;
		cout << endl;


	}

public:


	static void ShowLogInRegisterScreen() {

		
		if (!CheckAccessRights(clsUser::pLogInRegister)) {

			return;
		}

		vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();
		string Title = "\t  Login Register List Screen";
		string SubTitle = "\t\t(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << "\n\n";

		cout << setw(8) << left << "" << "----------------------------------------------------";
		cout << "-------------------------------------------------------\n\n";
		cout << setw(8) << left << "" << " | " << left << setw(37) << "Date/Time";
		cout << "| " << left << setw(23) << "UserName";
		cout << "| " << left << setw(22) << "Password";
		cout << "| " << left << setw(20) << "Permissions";
		cout << "\n\n";
		cout << setw(8) << left << "" << "----------------------------------------------------";
		cout << "-------------------------------------------------------\n\n";

		if (vLoginRegisterRecord.size() == 0) {


			cout << "\t\t\t\tNo Logins Available In the System!\n";
		}
		else 

			for (clsUser::stLoginRegisterRecord Record : vLoginRegisterRecord) {

				_PrintRecordLogInRegister(Record);

			}

		cout << "\n\n";
		cout << setw(8) << left << "" << "----------------------------------------------------";
		cout << "-------------------------------------------------------\n\n";

	}

};

