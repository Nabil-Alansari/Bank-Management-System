#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"
class clsDeleteUserScreen : protected clsScreen
{
private:

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

	static void ShowDeleteUserScreen() {


		_DrawScreenHeader("\t  Delete User Screen");
		string UserName;
		char Answer = 'n';

		cout << "\nPlease Enter User Name: ";
		UserName = clsInputValidate<string>::ReadString();

		while (!clsUser::IsUserExist(UserName)) {

			cout << "\nUser name is not found , Choose another one: ";
			UserName = clsInputValidate<string>::ReadString();

		}

		clsUser User = clsUser::Find(UserName);

		_PrintUserCard(User);

		cout << "\nAre you sure you want delete this user? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			if (User.Delete()) {

				cout << "\nUser Deleted Successfully :-)\n";
				_PrintUserCard(User);
			}
			else {

				cout << "\nError User was not deleted :-(\n";
			}

		}
			 
	}

};

