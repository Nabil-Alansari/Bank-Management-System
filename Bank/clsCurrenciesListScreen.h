#pragma once
#include <iostream>
#include <iomanip>
#include "clsString.h"
#include "clsScreen.h"
#include "clsCurrency.h"
#include <vector>
using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
private: 

	static void _PrintRecordCurrency(clsCurrency Currency) {

		cout << setw(8) << left << "" << " | " << setw(30) << left << Currency.Country();
		cout << "| " << setw(8) << left << Currency.CurrencyCode();
		cout << "| " << setw(45) << left << Currency.CurrencyName();
		cout << "| " << setw(16) << left << Currency.Rate();
		cout << endl;
	}

public:

	static void ShowCurrenciseListScreen() {

		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();


		string Title = "\t  Currencies List Screen";
		string SubTitle = "\t     (" + to_string(vCurrencies.size()) + ") Currency.";

		clsScreen::_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "----------------------------------------------------";
		cout << "-------------------------------------------------------\n\n";
		cout << setw(8) << left << "" << " | " << left << setw(30) << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(45) << "Name";
		cout << "| " << left << setw(16) << "Rate/(1$)";
		cout << "\n\n";
		cout << setw(8) << left << "" << "----------------------------------------------------";
		cout << "-------------------------------------------------------\n\n";;

		if (vCurrencies.size() == 0) {

			cout << "\t\t\t\tNo Currency Available In the System!\n";

		}

		else {

			for (clsCurrency Currency : vCurrencies) {

				_PrintRecordCurrency(Currency);

			}

		}

		cout << "\n" << setw(8) << left << "" << "----------------------------------------------------";
		cout << "-------------------------------------------------------\n\n";

	}

};

