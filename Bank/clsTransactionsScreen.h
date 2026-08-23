#pragma once
#include <iostream>
#include <iomanip>
#include "clsMainScreen.h"
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private :

	enum enTransactionsMenueOptions {

		eDeposit = 1, eWithdraw = 2, eShowTotalBalances = 3 ,
		eTransfer = 4 , eShowTransferLog = 5 ,eShowMainMenue = 6
	};

	static short _ReadTransactionsOption() {

		cout << setw(37) << left << "\t\t\t\t\tChoose what do you want to do ? [1 to 6]? ";
		short Choice = clsInputValidate<short>::ReadNumberBetween(1, 6, "Invalid Number, Enter again\n");
		return Choice;
	}

	static void _GobackToTransactionsMenu() {

		cout << "\n\n\tPress any key to go back to Transaction Menue.\n";
		system("pause>0");
		clsTransactionsScreen::ShowTransactionsMenue();

	}

	static void _ShowDepositScreen() {

		//cout << "\nDeposit Screen will be here...";

		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen() {

		//cout << "\nWithdrae screen will be here...";
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen() {

		//cout << "\nTotal Balances will be here...";

		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static void _ShowTransferScreen() {

		clsTransferScreen::ShowTransferScreen();

	}

	static void _ShowTransferLogScreen() {

		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _PreformTransactionMenue(enTransactionsMenueOptions Option) {

		switch (Option) {

		case enTransactionsMenueOptions::eDeposit:

			system("cls");
			_ShowDepositScreen();
			_GobackToTransactionsMenu();
			break;

		case enTransactionsMenueOptions::eWithdraw:

			system("cls");
			_ShowWithdrawScreen();
			_GobackToTransactionsMenu();
			break;

		case enTransactionsMenueOptions::eShowTotalBalances:

			system("cls");
			_ShowTotalBalancesScreen();
			_GobackToTransactionsMenu();
			break;

		case enTransactionsMenueOptions::eTransfer:

			system("cls");
			_ShowTransferScreen();
			_GobackToTransactionsMenu();
			break;

		case enTransactionsMenueOptions::eShowTransferLog:

			system("cls");
			_ShowTransferLogScreen();
			_GobackToTransactionsMenu();
			break;

		case enTransactionsMenueOptions::eShowMainMenue:

			break;


		}
	
	}

public:

	static void ShowTransactionsMenue() {

		if (!CheckAccessRights(clsUser::enPermissions::pTransactions)) {

			return;
		}

		system("cls");

		_DrawScreenHeader("\t\tTransacions Screen");

		cout << setw(37) << left << "" << "================================================\n";
		cout << setw(37) << left << "" << "\t\t\tTransaction Menue\n";
		cout << setw(37) << left << "" << "================================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit." << endl;
		cout << setw(37) << left << "" << "\t[2] Withdraw." << endl;
		cout << setw(37) << left << "" << "\t[3] Total Balances." << endl;
		cout << setw(37) << left << "" << "\t[4] Transfer." << endl;
		cout << setw(37) << left << "" << "\t[5] Transfer Log." << endl;
		cout << setw(37) << left << "" << "\t[6] Main Menue." << endl;
		cout << setw(37) << left << "" << "================================================\n";

		_PreformTransactionMenue(enTransactionsMenueOptions(_ReadTransactionsOption()));


	}

};

