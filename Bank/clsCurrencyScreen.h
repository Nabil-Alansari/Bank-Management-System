#pragma once
#include <iostream>
#include <iomanip>
#include "clsString.h"
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{
private:

	enum enCurrencyMainMenueOptions {

		eListCurrencies = 1, eFindCurrency = 2, eUpdateCurrency = 3,
		eCalculatorCurrency = 4, eExit = 5
	};

	static short _ReadCurrencyMainMenueOption() {

		cout << setw(37) << left << "\t\t\t\t\tChoose what do you want to do ? [1 to 5]? ";
		short Choice = clsInputValidate<short>::ReadNumberBetween(1, 5, "Invalid Number, Enter again\n");
		return Choice;
	}

	static void _GobackToCurrencyMainMenue() {

		cout << "\n\tPress any key to go back to Currency Menue.\n";
		system("pause>0");

		clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();

	}

	static void _ShowListCurrenciesScreen() {

		//cout << "\nList Currencies Screen well be here...\n";

		clsCurrenciesListScreen::ShowCurrenciseListScreen();
	}

	static void _ShowFindCurrenciesScreen() {

		//cout << "\Find Currency Screen well be here...\n";

		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen() {

		//cout << "\nUpdate Currency Screen well be here...\n";

		clsUpdateRateScreen::ShowUpdateRateScreen();
	}

	static void _ShowCalculatorCurrenciesScreen() {

		//cout << "\Calculator Currency Screen well be here...\n";

		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PreformeCurrencyMainMenueOption(enCurrencyMainMenueOptions CurrencyMainMenueOption) {

		switch (CurrencyMainMenueOption) {

		case enCurrencyMainMenueOptions::eListCurrencies:

			system("cls");
			_ShowListCurrenciesScreen();
			_GobackToCurrencyMainMenue();
			break;

		case enCurrencyMainMenueOptions::eFindCurrency:

			system("cls");
			_ShowFindCurrenciesScreen();
			_GobackToCurrencyMainMenue();
			break;

		case enCurrencyMainMenueOptions::eUpdateCurrency:

			system("cls");
			_ShowUpdateRateScreen();
			_GobackToCurrencyMainMenue();
			break;

		case enCurrencyMainMenueOptions::eCalculatorCurrency:

			system("cls");
			_ShowCalculatorCurrenciesScreen();
			_GobackToCurrencyMainMenue();
			break;


		case enCurrencyMainMenueOptions::eExit:

			break;
		}

	}


public:

	static void ShowCurrenciesMenue() {

		system("cls");

		_DrawScreenHeader("\tCurrency Exchange Main Screen");

		cout << setw(37) << left << "" << "================================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
		cout << setw(37) << left << "" << "================================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies." << endl;
		cout << setw(37) << left << "" << "\t[2] Find Currency." << endl;
		cout << setw(37) << left << "" << "\t[3] Update Reate." << endl;
		cout << setw(37) << left << "" << "\t[4] Currency Calculator." << endl;
		cout << setw(37) << left << "" << "\t[5] Main Menue." << endl;
		cout << setw(37) << left << "" << "================================================\n";

		_PreformeCurrencyMainMenueOption(enCurrencyMainMenueOptions(_ReadCurrencyMainMenueOption()));

	}

};

