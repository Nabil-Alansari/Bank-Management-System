#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsCurrency.h"
#include "clsScreen.h"
using namespace std;

class clsUpdateRateScreen : protected clsScreen
{

private:

	static float _ReadNewRate() {

		float NewRate;

		cout << "\n\nUpdate Currency Rate:\n\n";

		cout << "--------------------------------\n\n";
		cout << "Enter New Rate: ";
		NewRate = clsInputValidate<float>::ReadNumber();
		return NewRate;


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

public:


	static void ShowUpdateRateScreen() {

		_DrawScreenHeader("\t  Update Currency Screen");

		string CurrencyCode;


		cout << "\nPlease Enter Currency Code: ";
		CurrencyCode = clsInputValidate<string>::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {

			cout << "\n\nCurrency was not Found , Choose another one: ";
			CurrencyCode = clsInputValidate<string>::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindCurrencyByCode(CurrencyCode);
		_PrintCurrencyCard(Currency);

		cout << "\nAre you sure want to update the rate of this Currency y/n ? ";
		char Answer = 'n';
		cin >> Answer;

		float NewRate = 0;

		if (Answer == 'y' || Answer == 'Y') {

			if (!Currency.IsEmpty()) {

				NewRate = _ReadNewRate();
				Currency.UpdateRate(NewRate);
				cout << "\n\nCurrency Rate Updated Sccessfully :-)\n";
				_PrintCurrencyCard(Currency);
			}

			else {

				cout << "\nError Currency was not Update because it's Empty\n";
			}

		}


	}
};

