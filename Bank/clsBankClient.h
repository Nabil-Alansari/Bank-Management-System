#pragma once
#include <iostream>
#include <string>
#include <vector> 
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"
#include "clsDate.h"
#include "clsUtil.h"
#include "Global.h"
using namespace std;


class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2};

	enMode _Mode;


	string _AccountNumber;
	string _PinCode;
	bool _MarkedForDelete = false;
	float _AccountBalance;

	static clsBankClient _ConvertLineToClinetObject(string Line, string Seperator = "#//#") {

		vector <string> vClientDate;

		vClientDate = clsString::SplitToVector(Line, Seperator);

		return clsBankClient(UpdateMode, vClientDate[0], vClientDate[1], vClientDate[2],
			vClientDate[3], vClientDate[4], _DecryptPassword(vClientDate[5]), stof(vClientDate[6]));


	}

	static string _ConvertClinetObjectToLine(clsBankClient Client, string Seperator = "#//#") {

		string stClientRecord = "";

		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.GetAccountNumber() + Seperator;
		stClientRecord += _EncryptPassword(Client.PinCode) + Seperator;
		stClientRecord += to_string(Client.AccountBalance) + Seperator;

		return stClientRecord;

	}

	static clsBankClient _GetEmptyClinetObject() {

		return clsBankClient(EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsBankClient> _LoadClientsDataFromFile() {

		vector <clsBankClient> vClients;
		string DataLine;
		fstream MyFile;

		MyFile.open("Clients.text", ios::in);

		if (MyFile.is_open()) {

			while (getline(MyFile, DataLine)) {

				vClients.push_back(clsBankClient::_ConvertLineToClinetObject(DataLine));
			}

			MyFile.close();

		}
		return vClients;
	}

	static void _SaveClientDateToFile(vector <clsBankClient> vClient) {

		fstream MyFile;
		string DataLine;
		MyFile.open("Clients.text", ios::out);

		if (MyFile.is_open()) {

			for (clsBankClient C : vClient) {

				if (C._MarkedForDelete == false) {
					DataLine = clsBankClient::_ConvertClinetObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}

		}
		MyFile.close();


	}

	void _Update() {

		vector <clsBankClient> vClient;

		vClient = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClient) {

			if (C._AccountNumber == GetAccountNumber()) {

				C = *this;
				break;
			}
		}

		_SaveClientDateToFile(vClient);

		
	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertClinetObjectToLine(*this));


	}

	void _AddDataLineToFile(string stDataLine) {

		fstream MyFile;

		MyFile.open("Clients.text", ios::app);

		if (MyFile.is_open()) {

			MyFile << stDataLine << endl;

		}
		MyFile.close();


	}

	string _PrepareTransferLog(double Amount , clsBankClient DestinationClient , string UserName , string Seprator = "#//#") {

		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seprator;
		TransferLogRecord += this->GetAccountNumber() + Seprator;
		TransferLogRecord += DestinationClient.GetAccountNumber() + Seprator;
		TransferLogRecord += to_string(Amount) + Seprator;
		TransferLogRecord += to_string(this->AccountBalance) + Seprator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seprator;
		TransferLogRecord += UserName;
		return TransferLogRecord;

	}

	void _RegisterTransferLog(double Amount , clsBankClient DestinationClient , string UserName) {

		string DataLine = _PrepareTransferLog(Amount, DestinationClient, UserName);

		fstream MyFile;

		MyFile.open("TransferLog.text", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << DataLine << endl;

		}
		MyFile.close();

	}

	struct stTransferLog;
	
	static stTransferLog ConvertTransfetRegisterLogRecord(string Line , string Seprator = "#//#") {

		vector <string> stDataLine = clsString::SplitToVector(Line, Seprator);
		stTransferLog TransferLog;

		TransferLog.DateTime = stDataLine[0];
		TransferLog.SourceAccountNumber = stDataLine[1];
		TransferLog.DestinationAccountNumber = stDataLine[2];
		TransferLog.Amount = stod(stDataLine[3]);
		TransferLog.srcBalanceAfter = stod(stDataLine[4]);
		TransferLog.destBalanceAfter = stod(stDataLine[5]);
		TransferLog.UserName = stDataLine[6];
		return TransferLog;
	}

	static string _EncryptPassword(string Password) {

		string Encrypt = "";
		char cEncrypt;

		for (short i = 0; i < Password.size(); i++) {

			if (!Password.empty()) {

				cEncrypt = char(Password[i] + 12);

				Encrypt += cEncrypt;
			}

		}
		return Encrypt;

	}

	static string _DecryptPassword(string Encrypt, short Decryptionkey = 12) {


		string Password = "";
		char cEncrypt;

		for (short i = 0; i < Encrypt.size(); i++) {

			if (!Encrypt.empty()) {

				cEncrypt = char(Encrypt[i] - Decryptionkey);

				Password += cEncrypt;
			}

		}
		return Password;

	}

public:

	clsBankClient(enMode Mode , string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone) {

		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;

	}

	struct stTransferLog {

		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		double Amount = 0;
		double srcBalanceAfter = 0;
		double destBalanceAfter = 0;
		string UserName;

	};

	bool IsEmpty() {

		return (_Mode == enMode::EmptyMode);
	}

	string GetAccountNumber() {

		return _AccountNumber;

	}

	void SetPinCode(string PinCode) {

		_PinCode = PinCode;
	}

	string GetPinCode() {

		return _PinCode;

	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance) {

		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance() {

		return _AccountBalance;

	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	static clsBankClient Find(string AccountNumber) {

		vector <clsBankClient> vClinet;
		fstream MyFile;

		MyFile.open("Clients.text", ios::in);

		if (MyFile.is_open()) {

			string Line;



			while (getline(MyFile, Line)) {		
				
				clsBankClient Clinet = _ConvertLineToClinetObject(Line);

				if (Clinet._AccountNumber == AccountNumber) {

					MyFile.close();
					return Clinet;
				}
				vClinet.push_back(Clinet);
			}

			MyFile.close();
		}

		return _GetEmptyClinetObject();
	}

	static clsBankClient Find(string AccountNumber ,string PinCode) {

		vector <clsBankClient> vClinet;
		fstream MyFile;

		MyFile.open("Clinets.text", ios::in);

		if (MyFile.is_open()) {

			string Line;

			clsBankClient Clinet = _ConvertLineToClinetObject(Line);

			while (getline(MyFile, Line)) {

				if (Clinet._AccountNumber == AccountNumber && Clinet._PinCode == PinCode) {

					MyFile.close();
					return Clinet;
				}
				vClinet.push_back(Clinet);
			}

			MyFile.close();
		}

		return _GetEmptyClinetObject();
	}

	static bool IsClientExist(string AccountNumber) {

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());

	}

	enum enSaveResult { svFalidEmptyObject = 0, scSucceeded = 1 , svFaildAccountNumberExists };

	enSaveResult Save() {

		switch (_Mode) {

		case enMode::EmptyMode :

			return svFalidEmptyObject;

		case enMode::UpdateMode:

			_Update();

			return scSucceeded;

			break;

		case enMode::AddNewMode:

			if (clsBankClient::IsClientExist(_AccountNumber)) {

				return enSaveResult::svFaildAccountNumberExists;
			}
			else {


				_AddNew();

				_Mode = UpdateMode;
				return enSaveResult::scSucceeded;
				break;
			}

			


		}

	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {

		return clsBankClient(AddNewMode, "", "", "", "", AccountNumber, "", 0);

	}

	bool Delete() {

		vector <clsBankClient> _vClientBank = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClientBank) {

			if (C._AccountNumber == _AccountNumber) {

				C._MarkedForDelete = true;
				break;

			}

		}

		_SaveClientDateToFile(_vClientBank);


		*this = _GetEmptyClinetObject();

		return IsEmpty();


	}

	static vector <clsBankClient> GetClientsList() {

		return _LoadClientsDataFromFile();

	}

	static double GetTotalBalaces() {

		vector <clsBankClient> vClient = _LoadClientsDataFromFile();

		double TotalBalances = 0;

		for (clsBankClient C : vClient) {


			TotalBalances += C.AccountBalance;

		}

		return TotalBalances;


	}

	//This backend of Transaction

	void Deposit(double Amount) {

		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {

		if (Amount > AccountBalance) {

			return false;
		}
		else {
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

    bool Transfer(double Amount, clsBankClient& DestinationClient) {

		if (Amount > AccountBalance) {

			return false;
		}
		else {

			Withdraw(Amount);
			DestinationClient.Deposit(Amount);
			_RegisterTransferLog(Amount, DestinationClient, CurrentUser.UserName);
			return true;

		}
	}

	static vector <stTransferLog> GetTransfetRegisterLogList() {

		vector <clsBankClient::stTransferLog> stTransferLog;
		string Line;

		fstream MyFile;

		MyFile.open("TransferLog.text", ios::in);

		if (MyFile.is_open()) {

			while (getline(MyFile, Line)) {

				stTransferLog.push_back(ConvertTransfetRegisterLogRecord(Line));

			}

		}
		MyFile.close();

		return stTransferLog;
	}
};











