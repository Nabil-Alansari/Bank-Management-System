#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"

class clsUser : public clsPerson
{
private:

	enum enMode {EmptyMode = 1 , UpdateMode = 2 , AddNewMode = 3};

	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;

	bool MarkForDelete = false;

	static clsUser _ConvertLineUserToObject(string Line, string Seprator = "#//#") {

		vector <string> vUser;

		vUser = clsString::SplitToVector(Line, Seprator);

		return clsUser(UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3],
			vUser[4], vUser[5], stoi(vUser[6]));
	}

	static string _ConvertUserObjectToLine(clsUser User, string Seprator = "#//#") {

		string Line;

		Line += User.FirstName + Seprator;
		Line += User.LastName + Seprator;
		Line += User.Email + Seprator;
		Line += User.Phone + Seprator;
		Line += User._UserName + Seprator;
		Line += clsUtil::EncryptText(User._Password) + Seprator;
		Line += to_string(User._Permissions) + Seprator;
		return Line;

	}

	static clsUser _GetEmptyUserObject() {

		return clsUser (EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsUser> _LoadUsersDataFromFile() {

		vector <clsUser> vUsers;

		fstream MyFile;

		MyFile.open("Users.text", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				vUsers.push_back(_ConvertLineUserToObject(Line));
			}
			
		}
		MyFile.close();
		return vUsers;

	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers) {

		fstream MyFile;

		MyFile.open("Users.text", ios::out);

		if (MyFile.is_open()) {

			for (clsUser User : vUsers) {

				if (User.MarkForDelete == false) {

					MyFile << _ConvertUserObjectToLine(User) << endl;
				}

			}

		}
		MyFile.close();
	}

	void _AddDataLine(string DataLine) {

		fstream MyFile;

		MyFile.open("Users.text", ios::app);

		if (MyFile.is_open()) {

			MyFile << DataLine << endl;
		}
		MyFile.close();

	}

	void _AddNew() {

		_AddDataLine(_ConvertUserObjectToLine(*this));

	}

	void _Update() {

		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers) {

			if (User._UserName == GetUserName()) {

				User = *this;
				_SaveUsersDataToFile(vUsers);
				break;
			}
		}

	}

    string _PrepareLogInRecord(string Seprator = "#//#") {

		string Line;
		clsDate Date;

		Line += clsDate::GetSystemDateTimeString();
		Line += Seprator + UserName;
		Line += Seprator + to_string(Permissions);
		return Line;

	}

	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertLoginRegisterRecord(string Line , string Seprator = "#//#") {

		vector <string> LoginRegisterDataLine = clsString::SplitToVector(Line, Seprator);

		stLoginRegisterRecord LoginRegisterRecord;

		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.Username = LoginRegisterDataLine[1];
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[2]);

		return LoginRegisterRecord;
	}



public :

	enum enPermissions {
		eAll = -1, pListClient = 1, pAddNewClient = 2,
		pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16,
		pTransactions = 32, pMangeUsers = 64, pLogInRegister = 128
	};

	struct stLoginRegisterRecord {

		string DateTime;
		string Username;
		int Permissions;

	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string UsetName, string Password, int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone) {

		_Mode = Mode;
		_UserName = UsetName;
		_Password = Password;
		_Permissions = Permissions;

	}

    void SetUserName(string UserName) {

		_UserName = UserName;

	}

	string GetUserName() {

		return _UserName;
	}

	_declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password) {

		_Password = Password;
	}

	string GetPassword() {

		return _Password;
	}

	_declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions) {

		_Permissions = Permissions;
	}

	int GetPermissions(){
	
		return _Permissions;

	}

	_declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	 bool IsEmpty() {

		return (_Mode == EmptyMode);
	}

	static clsUser Find(string UserName) {

		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser User : vUsers) {

			if (User.UserName == UserName) {

				return User;
			}

		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Pass) {

		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser User : vUsers) {

			if (User.UserName == UserName && User.Password == clsUtil::EncryptText(Pass)) {

				return User;
			}

		}
		return _GetEmptyUserObject();

	}

	static bool IsUserExist(string UserName) {

		clsUser User = Find(UserName);

		return (!User.IsEmpty());
	}

	 bool Delete() {

		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers) {

			if (User.UserName == _UserName) {

				User.MarkForDelete = true;
				break;

			}
		}
		
		_SaveUsersDataToFile(vUsers);

		*this = _GetEmptyUserObject();

		return IsEmpty();
	}

	 enum enSaveResult {svFalidEmptyObject = 1 , scSucceeded = 2 , svFaildUserNameExists = 3};

	 enSaveResult Save() {

		 switch (_Mode) {

		 case enMode::EmptyMode:

			 return svFalidEmptyObject;

		 case enMode::UpdateMode:

			 _Update();
			 return scSucceeded;

		 case enMode::AddNewMode:

			 if (clsUser::IsUserExist(_UserName)) {

				 return svFaildUserNameExists;

			 }
			 else {

				 _Mode = UpdateMode;
				 _AddNew();
				 return scSucceeded;

			 }
		 }
	 }

	 static vector <clsUser> GetListUsers() {

		 return _LoadUsersDataFromFile();

	 }

	 static clsUser GetAddNewUser(string UserName) {

		 return clsUser(AddNewMode, "", "", "", "", UserName, "", eAll);
	 }

	 bool ChecAccessPermissions(clsUser::enPermissions Permissions) {

		 if (this->Permissions == enPermissions::eAll) {

			 return true;
		 }
		 
		 if ((Permissions & this->Permissions) == Permissions) {

			 return true;
		 }
		 else {

			 return false;
		 }
	 }

	 void RegisterLogIn() {

		 string stDataLine = _PrepareLogInRecord();
		 fstream MyFile;

		 MyFile.open("LoginRegister.text",ios::out | ios::app);

		 if (MyFile.is_open()) {

			 MyFile << stDataLine << endl;

		 }
		 MyFile.close();

	 }

	 static vector <stLoginRegisterRecord> GetLoginRegisterList() {

		 vector <stLoginRegisterRecord> vLoginRegisterRecord;

		 string Line;

		 fstream MyFile;
		 MyFile.open("LoginRegister.text", ios::in);

		 if (MyFile.is_open()) {

			 while (getline(MyFile, Line)) {

				 vLoginRegisterRecord.push_back(_ConvertLoginRegisterRecord(Line));
			 }

		 }MyFile.close();

		 return vLoginRegisterRecord;

	 }

};

