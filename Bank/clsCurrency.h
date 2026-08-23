#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>
using namespace std;


class clsCurrency
{

private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;
	
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line , string Seprator = "#//#") {

		vector <string> vCurrencyLine = clsString::SplitToVector(Line, Seprator);

		clsCurrency Currency(UpdateMode,vCurrencyLine[0], vCurrencyLine[1], vCurrencyLine[2],
			 stof(vCurrencyLine[3]));

		return Currency;

	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seprator = "#//#") {

		string stLine = "";

		stLine += Currency._Country + Seprator;
		stLine += Currency._CurrencyCode + Seprator;
		stLine += Currency._CurrencyName + Seprator;
		stLine += to_string(Currency._Rate);
		return stLine;

	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile() {

		string Line;
		vector <clsCurrency> vCurrencies;

		fstream MyFile;

		MyFile.open("Currencies.text", ios::in);

		if (MyFile.is_open()) {

			while (getline(MyFile, Line)) {

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				
				vCurrencies.push_back(Currency);

			}

		}
		MyFile.close();

		return vCurrencies;
	}

	static void _SaveCurrenciesObjectToFile(vector <clsCurrency> vCurrencies) {

		string Line;
	

		fstream MyFile;

		MyFile.open("Currencies.text", ios::out);

		if (MyFile.is_open()) {

			for (clsCurrency Currency : vCurrencies) {

				Line = _ConvertCurrencyObjectToLine(Currency);

				MyFile << Line << endl;

			}
		}
		MyFile.close();

	}

     void _Update() {

	static	vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& C : vCurrencies) {

			if (C.CurrencyCode() == CurrencyCode()) {

				C = *this;
				_SaveCurrenciesObjectToFile(vCurrencies);
				break;
			}

		}

	}

public :

	clsCurrency() {


	}

	clsCurrency(enMode Mode ,string Country, string CurrencyCode, string CurrencyName , float Rate) {

		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;

	}

	bool IsEmpty() {

		return (_Mode == EmptyMode);
	}

	string Country() {

		return _Country;
	}

	string CurrencyCode() {

		return _CurrencyCode;

	}

	string CurrencyName() {

		return _CurrencyName;
	}

	void UpdateRate(float NewRate) {

		_Rate = NewRate;
		_Update();
	}

	float Rate() {

		return _Rate;
	}
	
	static clsCurrency FindCurrencyByCode(string CurrencyCode) {

		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;

		MyFile.open("Currencies.text", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (Currency.CurrencyCode() == CurrencyCode) {

					MyFile.close();

					return Currency;
				}

			}
			MyFile.close();

			return clsCurrency(EmptyMode,"", "", "", 0);

		}
	}

	static clsCurrency FindCurrencyByCountry(string Country){

		Country = clsString::UpperAllString(Country);

		fstream MyFile;

		MyFile.open("Currencies.text", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				clsCurrency Currecny = _ConvertLineToCurrencyObject(Line);
			
				if (clsString::UpperAllString((Currecny.Country())) == Country) {

					MyFile.close();
					return Currecny;

				}

			}

		}
		MyFile.close();

		return clsCurrency(EmptyMode, "", "", "", 0);
	
	}

	static bool IsCurrencyExist(string CurrencyCode) {

		clsCurrency Currency = clsCurrency::FindCurrencyByCode(CurrencyCode);

		return (!Currency.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList() {

		vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		return vCurrencies;
	}

	float ConvertToUSD(float Amount) {

		return (float)(Amount / Rate());
	}

	float ConverToOtherCurrency(float Amount, clsCurrency Currency2) {

		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD") {

			return AmountInUSD;
		}
		else {

			return (float)(AmountInUSD * Currency2.Rate());
		}

	}

	static float CurrencyCalculator(float Amount, clsCurrency Currency1, clsCurrency Currency2) {

		float AmountAfterExchange;

		if (Currency1.CurrencyCode() == "USD") {

			return AmountAfterExchange = Currency2.Rate() * Amount;


		}

		if (Currency2.CurrencyCode() == "USD") {


			return AmountAfterExchange = Amount / Currency1.Rate();


		}


		AmountAfterExchange = (Amount / Currency1.Rate()) * Currency2.Rate();

		return AmountAfterExchange;


	}

};

