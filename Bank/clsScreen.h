#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "Global.h"
#include "clsDate.h"

using namespace std;


class clsScreen
{

protected :

	static void _DrawScreenHeader(string Title, string SubTitle = "") {

		cout << setw(37) << left << "" << "------------------------------------------------";
		cout << "\n\n\t\t\t\t\t" << Title << endl;

		if (SubTitle != "") {


			cout << "\t\t\t\t\t" << SubTitle << endl;

		}
		cout << endl;
		cout << setw(37) << left << "" << "------------------------------------------------" << endl;

		cout << "\n" << setw(37) << left << "" << "User: " << CurrentUser.UserName;
		cout << "\n" << setw(37) << left << "" << "Date:" << clsDate::DateToString(clsDate()) << endl;
		cout << "\n";

	}

	static bool CheckAccessRights(clsUser::enPermissions Permissions) {


		if (!CurrentUser.ChecAccessPermissions(Permissions)) {

			cout << "\t\t\t\t\t---------------------------------------------";
			cout << "\n\n\t\t\t\t\t    Access Denied , Contact your Admin!";
			cout << "\n\t\t\t\t\t---------------------------------------------\n\n";
			return false;
		}
		else {

			return true;
		}

	}

};

