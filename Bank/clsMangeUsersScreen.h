#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsListUsers.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;

class clsMangeUsersScreen : protected clsScreen
{
private:

	enum enMangeUsersMenueOptions {

		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
	};

	static short _ReadMangeUsersMenueOption() {

		cout << setw(37) << left << "\t\t\t\t\tChoose what do you want to do ? [1 to 6]? ";
		short Choice = clsInputValidate<short>::ReadNumberBetween(1, 6, "Invalid Number, Enter again\n");
		return Choice;
	}

	static void _GoBackToMangeUsresMenue() {

		cout << "\n\n\tPress any key to go back to Mange Users Menue.\n";
		system("pause>0");
		clsMangeUsersScreen::ShowMangeUsersMenue();
	}

	static void _ShowListUsersScreen(){
	
		//cout << "List User Scree Will be here...\n";

		clsListUsers::ShowListUsersScreen();

	}

	static void _ShowAddNewUserScreen(){
	
		//cout << "Add New User Screen Will be here...\n";
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen(){
	
		//cout << "Delte User Screen Will be here...\n";
		clsDeleteUserScreen::ShowDeleteUserScreen();

	}

	static void _ShowUpdateUserScreen(){

		//cout << "Update User Screen Will be here...\n";
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen(){

		//cout << "Find User Screen Will be here...\n";m
		clsFindUserScreen::ShowFindUserScreen();

	}

	static void _PerformMangeUsersMenueOption(enMangeUsersMenueOptions MenueOption) {

		switch (MenueOption) {

		case enMangeUsersMenueOptions::eListUsers:

			system("cls");
			_ShowListUsersScreen();
			_GoBackToMangeUsresMenue();
			break;
		case enMangeUsersMenueOptions::eAddNewUser:

			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToMangeUsresMenue();
			break;

		case enMangeUsersMenueOptions::eDeleteUser:

			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToMangeUsresMenue();
			break;

		case enMangeUsersMenueOptions::eUpdateUser:

			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToMangeUsresMenue();
			break;

		case enMangeUsersMenueOptions::eFindUser:

			system("cls");
			_ShowFindUserScreen();
			_GoBackToMangeUsresMenue();
			break;

		case enMangeUsersMenueOptions::eMainMenue:

			// do nothing here...
			break;
		}
	}

public: 

	static void ShowMangeUsersMenue() {


		if (!CheckAccessRights(clsUser::enPermissions::pMangeUsers)) {

			return;
		}

		system("cls");
		_DrawScreenHeader("\t\tMange Users Screen");

		cout << setw(37) << left << "" << "================================================\n";
		cout << setw(37) << left << "" << "\t\t\t\Mange User Menue\n";
		cout << setw(37) << left << "" << "================================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users." << endl;
		cout << setw(37) << left << "" << "\t[2] Add New User." << endl;
		cout << setw(37) << left << "" << "\t[3] Delete User." << endl;
		cout << setw(37) << left << "" << "\t[4] Update User." << endl;
		cout << setw(37) << left << "" << "\t[5] Find User." << endl;
		cout << setw(37) << left << "" << "\t[6] Main Menue." << endl;
		cout << setw(37) << left << "" << "================================================\n";

		_PerformMangeUsersMenueOption(enMangeUsersMenueOptions(_ReadMangeUsersMenueOption()));

	}

};

