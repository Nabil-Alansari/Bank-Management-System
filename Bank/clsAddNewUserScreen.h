#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
using namespace std;


class clsAddNewUserScreen : protected clsScreen
{

private :

	static 	void _ReadUserInfo(clsUser &User) {

		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate<string>::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate<string>::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate<string>::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate<string>::ReadString();


		cout << "\nEnter Password: ";
		
		User.Password = clsInputValidate<string>::ReadString();

		cout << "\nEnter Permissions: ";

		User.Permissions = _ReadPermissionsToSet();


	}

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

	static int _ReadPermissionsToSet() {

		int Permissions = 0;
		char Answer = 'n';

		cout << "\nDo you want to give full access? y/n ? ";
		cin >> Answer; 

		if (Answer == 'y' || Answer == 'Y') {

			return -1;
		}

		cout << "\nShow Client List? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			Permissions += clsUser::enPermissions::pListClient;
		}

		cout << "\nAdd New Client? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete Client? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			Permissions += clsUser::enPermissions::pUpdateClient;
		}

		cout << "\nFind Client? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			Permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "\nTransaction? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			Permissions += clsUser::enPermissions::pTransactions;
		}

		cout << "\nMange Users? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			Permissions += clsUser::enPermissions::pMangeUsers;
		}

		cout << "\nShow Login Register? y/n ? ";
		cin >> Answer;
		
		if (Answer == 'y' || Answer == 'Y') {

			Permissions += clsUser::enPermissions::pLogInRegister;

		}
		return Permissions;
	}

public:

	static void ShowAddNewUserScreen() {

		clsScreen::_DrawScreenHeader("\t  Add New User Screen");

		cout << "\n\nPlease Enter User Name: ";
		string UserName = clsInputValidate<string>::ReadString();

		while (clsUser::IsUserExist(UserName)) {

			cout << "\nUser Name Is Already Used, Choose another one: ";
			UserName = clsInputValidate<string>::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUser(UserName);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResult Save;

		Save = NewUser.Save();

		switch (Save) {

		case clsUser::enSaveResult::scSucceeded:

			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintUserCard(NewUser);

			break;

		case clsUser::enSaveResult::svFalidEmptyObject:

			cout << "\nError account was not save because it's Empty\n";
			break;

		case clsUser::enSaveResult::svFaildUserNameExists:

			cout << "\nAccount Number Is Already Used\n";
			break;
		}
	}

};

