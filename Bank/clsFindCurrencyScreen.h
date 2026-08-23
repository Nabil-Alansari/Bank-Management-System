#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsCurrency.h"
#include "clsScreen.h"
using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
	enum enFindOption { eByCode = 1 , eByCountry = 2};

	static short _ReadFindOption() {

		cout << "\nFind By: [1] Code or [2] Country ? ";
		short Option = clsInputValidate<short>::ReadNumberBetween(1,2,"\nInvalid Number, Enter agin ");
		return Option;
	}

	static void _PrintCurrencyCard(clsCurrency Currency) {

		cout << "\nCurrency Card:\n\n";
		cout << "----------------------------------\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate() << endl;

		cout << "\n----------------------------------\n";
	}

	static clsCurrency _FindBy(enFindOption Option) {

		clsCurrency Currency;

		switch (Option) {

		case enFindOption::eByCode:

			cout << "\nPlease Enter CurrencyCode: ";

			Currency = clsCurrency::FindCurrencyByCode(clsInputValidate<string>::ReadString());
			return Currency;

		case enFindOption::eByCountry:

			cout << "\nPlease Enter Country Name: ";
			Currency = clsCurrency::FindCurrencyByCountry(clsInputValidate<string>::ReadString());
			return Currency;
		}
	}

public:

	static void ShowFindCurrencyScreen() {

		_DrawScreenHeader("\t  Find Currency Screen");

		short Option = _ReadFindOption();

		clsCurrency Currency = _FindBy(enFindOption(Option));

		if (!Currency.IsEmpty()) {

			cout << "\n\nCurrency Found :-)\n";

			_PrintCurrencyCard(Currency);
		}
		else {

			cout << "\n\nCurrency was not Found :-(\n";
		}

	}

};

