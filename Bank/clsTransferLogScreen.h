#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsBankClient.h"
#include "clsScreen.h"

class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintRecordTransferLog(clsBankClient::stTransferLog TransferLog) {

		cout << setw(8) << left << "" << " | " << setw(25) << left << TransferLog.DateTime;
		cout << "| " << setw(8) << left << TransferLog.SourceAccountNumber;
		cout << "| " << setw(8) << left << TransferLog.DestinationAccountNumber;
		cout << "| " << setw(10) << left << TransferLog.Amount;
		cout << "| " << setw(12) << left << TransferLog.srcBalanceAfter;
		cout << "| " << setw(12) << left << TransferLog.destBalanceAfter;
		cout << "| " << setw(12) << left << TransferLog.UserName;
		cout << endl;
	}

public:

	static void ShowTransferLogScreen() {

		vector <clsBankClient::stTransferLog> vTransferLog = clsBankClient::GetTransfetRegisterLogList();
		
		string Title = "\t  Transfer Log List Screen";
		string SubTitle = "\t\t(" + to_string(vTransferLog.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "----------------------------------------------------";
		cout << "-------------------------------------------------------\n\n";
		cout << setw(8) << left << "" << " | " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(8) << "s.Acct";
		cout << "| " << left << setw(8) << "d.Acct";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(12) << "s.Balance";
		cout << "| " << left << setw(12) << "d.Balance";
		cout << "| " << left << setw(12) << "User";
		cout << "\n\n";
		cout << setw(8) << left << "" << "----------------------------------------------------";
		cout << "-------------------------------------------------------\n\n";

		if (vTransferLog.size() == 0) {


			cout << "\t\t\t\tNo Logins Available In the System!\n";
		}
		else

			for (clsBankClient::stTransferLog Record : vTransferLog) {

				_PrintRecordTransferLog(Record);

			}

		cout << "\n\n";
		cout << setw(8) << left << "" << "----------------------------------------------------";
		cout << "-------------------------------------------------------\n\n";

		
	}

};

