#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsMangeUsersScreen.h"
#include "clsLogInRegisterScreen.h"
#include "clsCurrencyScreen.h"
#include "Global.h"
using namespace std;


class clsMainScreen : protected clsScreen
{
private:
	
	enum enMainMenueOptions {

		eListClients = 1 , eAddNewClient = 2, eDeleteClient = 3 , eUpdateClient =4,
		eFindClient = 5 , eShowTransactionMainMenu = 6, eMangeUsers = 7 ,
		eLogInRegister = 8 , eShowCurrecnyMainMenue = 9 , eExit = 10
	};

	static short _ReadCurrenciesMainMenueOption() {

		cout << setw(37) << left << "\t\t\t\t\tChoose what do you want to do ? [1 to 10]? ";
		short Choice = clsInputValidate<short>::ReadNumberBetween(1, 10, "Invalid Number, Enter again\n");
		return Choice;
	}

	static void _GobackToMainMenu() {

		cout << "\n\tPress any key to go back to Main Menue.\n";
		system("pause>0");
		clsMainScreen::ShowMainMenue();

	}

	static void _ShowAllClientScreen() {

		clsClientListScreen::ShowClientsList();


	}

	static void _ShowAddNewClientScreen() {

		clsAddNewClientScreen::ShowAddNewClientScreen();

	}

	static void _ShowDeleteClientScreen() {

		//cout << "\nDelete Client Screen Will be here...\n";

		clsDeleteClientScreen::ShowDeleteClientScreen();

	}

	static void _ShowUpdateClientScreen() {

		//cout << "\nUpdate Client Screen Will be here...\n";
		
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen() {

		//cout << "\nFind Client Screen Will be here...\n";

		clsFindClientScreen::ShowFindClientScreen();
	}
	
	static void _ShowTransactionScreen() {

		//cout << "\nTransaction Screen Will be here...\n";
		clsTransactionsScreen::ShowTransactionsMenue();
	}

	static void _ShowLogInregisterScreen() {

		clsLogInRegisterScreen::ShowLogInRegisterScreen();
	}

	static void _ShowMangeUserScreen() {

		//cout << "\nMange Users Screen Will be here...\n";

		clsMangeUsersScreen::ShowMangeUsersMenue();

	}

	static void _ShowCurrencyExchangeMainScreen() {

		clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();

	}

	/*static void _ShowEndScreen() {

		cout << "\nEnd Screen Will be here...\n";
	}*/

	static void _Logout() {

		CurrentUser = clsUser::Find("", "");

		// You can not Add Show Login Screen is heere because compiler giv erroe is sercal stack

	}

	static void _PreformMainMenueOption(enMainMenueOptions MainMenueOption) {

		switch (MainMenueOption) {

		case enMainMenueOptions::eListClients: {

			system("cls");
				_ShowAllClientScreen();
			_GobackToMainMenu();
			break;
		}
		case enMainMenueOptions::eAddNewClient: {

			system("cls");
			_ShowAddNewClientScreen();
			_GobackToMainMenu();
			break;
		}
		case enMainMenueOptions::eDeleteClient: {

			system("cls");
			_ShowDeleteClientScreen();
			_GobackToMainMenu();
			break;
		}
		case enMainMenueOptions::eUpdateClient: {

			system("cls");
			_ShowUpdateClientScreen();
			_GobackToMainMenu();
			break;
		}
		case enMainMenueOptions::eFindClient: {

			system("cls");
			_ShowFindClientScreen();
			_GobackToMainMenu();
			break;
		}

		case enMainMenueOptions::eShowTransactionMainMenu: {

			system("cls");
			_ShowTransactionScreen();
			_GobackToMainMenu();
			break;
		}
		case enMainMenueOptions::eMangeUsers: {

			system("cls");
			_ShowMangeUserScreen();
			_GobackToMainMenu();
			break;

		}

		case enMainMenueOptions::eLogInRegister:

		{

			system("cls");
			_ShowLogInregisterScreen();
			_GobackToMainMenu();
			break;
		}

		case enMainMenueOptions::eShowCurrecnyMainMenue: {

			system("cls");
			_ShowCurrencyExchangeMainScreen();
			_GobackToMainMenu();
			break;

		}

		case enMainMenueOptions::eExit: {

			system("cls");
			_Logout();
			break;

		}

		}

	}


public:

	static void ShowMainMenue() {

		system("cls");
		_DrawScreenHeader("\t\tMain Screen");

		cout << setw(37) << left << "" << "================================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "================================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List." << endl;
		cout << setw(37) << left << "" << "\t[2] Add New Client." << endl;
		cout << setw(37) << left << "" << "\t[3] Delete Client." << endl;
		cout << setw(37) << left << "" << "\t[4] Update Client." << endl;
		cout << setw(37) << left << "" << "\t[5] Find Client." << endl;
		cout << setw(37) << left << "" << "\t[6] Transaction." << endl;
		cout << setw(37) << left << "" << "\t[7] Mange Users." << endl;
		cout << setw(37) << left << "" << "\t[8] Login Register." << endl;
		cout << setw(37) << left << "" << "\t[9] Currency Exchange." << endl;
		cout << setw(37) << left << "" << "\t[10] Logout." << endl;
		cout << setw(37) << left << "" << "================================================\n";

		_PreformMainMenueOption(enMainMenueOptions(_ReadCurrenciesMainMenueOption()));

	}

	
	
};



