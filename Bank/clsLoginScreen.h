#pragma once
#include <iostream>
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "clsScreen.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{
private:

	
	static bool _Login() {

	     short FaildLoginCount = 0;
		bool LoginFaild = false;
		string Username, Password;
		do {

			if (LoginFaild) {

				FaildLoginCount++;
				
				cout << "\nInvlaid Username/Password!";
				cout << "\nYou have " << (3-FaildLoginCount)
					<< " Trial(s) to login.\n\n";
			}

			if (FaildLoginCount == 3) {

				cout << "\n\nYou are Locked after 3 faild trials\n";
				return false;
			}

			cout << "\nEnter Username: ";
			Username = clsInputValidate<string>::ReadString();
			cout << "\nEnter Password: ";
			Password = clsInputValidate<string>::ReadString();

			CurrentUser = clsUser::Find(Username, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);


		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;


	}

public:

	static bool ShowLoginScreen() {

		_DrawScreenHeader("\t\tLogin Screen");
		return _Login();
	}

};

