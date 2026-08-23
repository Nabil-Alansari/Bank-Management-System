#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"
using namespace std;

class clsFindUserScreen :protected clsScreen
{
private :

	static void _PrintUserCard(clsUser User) {

		cout << "\nClient Card:";
		cout << "\n---------------------------------";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFullName    : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions    : " << User.Permissions;
		cout << "\n---------------------------------";
		cout << endl;
	}

public:

	static void ShowFindUserScreen() {

		_DrawScreenHeader("\t  Find User Screen");

		string UserName;

		cout << "\nPlease enter user name: ";
		UserName = clsInputValidate<string>::ReadString();

		while (!clsUser::IsUserExist(UserName)) {

			cout << "\nUser is not found , Choose another one: ";
			UserName = clsInputValidate<string>::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		if (!User.IsEmpty()) {

			cout << "\nUser Found :-)\n";

		}
		else {

			cout << "\nUser was not Found :-(\n";
		}

		_PrintUserCard(User);


	}


};

