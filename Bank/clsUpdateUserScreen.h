#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"

class clsUpdateUserScreen : protected clsScreen
{
private:

	static 	void _ReadUserInfo(clsUser& User) {

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

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pLogInRegister;
		}
		return Permissions;
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

public:

	static void ShowUpdateUserScreen() {

		_DrawScreenHeader("\t  Update User Screen");

		string UserName;

		cout << "\nPlease enter user name: ";
		UserName = clsInputValidate<string>::ReadString();

		while (!clsUser::IsUserExist(UserName)) {

			cout << "\nUser is not found , Choose another one: ";
			UserName = clsInputValidate<string>::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		_PrintUserCard(User);

		cout << "Are you sure you want update user? y/n ? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			clsUser::enSaveResult Save;

			cout << "\n\n------------------------------\n";
			cout << "\tUpdate User Info";
			cout << "\n------------------------------\n";

			_ReadUserInfo(User);

			Save = User.Save();

			switch (Save) {

			case clsUser::enSaveResult::svFalidEmptyObject:

				cout << "\n\nError user was not update because empty :-(\n";
				break;

			case clsUser::enSaveResult::scSucceeded:

				cout << "\n\nUser Updated Successfully :-)\n";

				cout << "\n\nUser after update info.\n";

				_PrintUserCard(User);
				
				break;

			}

		}

	}

};

