#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{

private:

	static float _ReadAmount() {

		float Amount;
		cout << "\nEnter Amount to Exchange: ";
		Amount = clsInputValidate<float>::ReadNumber();

		return Amount;

	}

	static void _PrintCurrencyCard(clsCurrency Currency) {


		cout << "\n\n----------------------------------\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate() << endl;

		cout << "\n----------------------------------\n";
	}

	static clsCurrency _GetCurrency(string Message) {
        
		string  CurrencyCode;
		cout << Message;

		CurrencyCode = clsInputValidate<string>::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {


			cout << "\n\nCurrency was not Found , Choose another one: ";
			CurrencyCode = clsInputValidate<string>::ReadString();

		}

		clsCurrency Currency = clsCurrency::FindCurrencyByCode(CurrencyCode);

		return Currency;


	}

	static void _PrintCalculationResult(float Amount, clsCurrency Currency1, clsCurrency Currency2) {


		cout << "\n\nConvert Form: ";

		_PrintCurrencyCard(Currency1);

		float AmounInUSD = Currency1.ConvertToUSD(Amount);

		cout << "\n" << Amount << " " << Currency1.CurrencyCode()
			<< " = " << AmounInUSD << " USD";

		if (Currency2.CurrencyCode() == "USD") {

			return;
		}


			cout << "\nConverting form USD to:\n\n";

			cout << "\To:";

			_PrintCurrencyCard(Currency2);

			float AmountInCurrency2 = Currency1.ConverToOtherCurrency(Amount, Currency2);

			cout << "\n" << Amount << " " << Currency1.CurrencyCode()
				 << " = " << AmountInCurrency2 << " " << Currency2.CurrencyCode();



	}

public:

	static void ShowCurrencyCalculatorScreen() {
	

		char Continue = 'y';

		while (toupper(Continue) == 'Y') {

			system("cls");
			_DrawScreenHeader("\t Currency Calculator Screen");

			clsCurrency Currency1, Currency2;

			Currency1 = _GetCurrency("\nPlease Enter Currency1 Code : ");
			Currency2 = _GetCurrency("\n\nPlease Enter Currency2 Code: ");

			float Amount = _ReadAmount();

			_PrintCalculationResult(Amount, Currency1, Currency2);

			cout << "\n\n Do you want to perform another calculation? y/n ?";
			cin >> Continue;
		}

	}
};

