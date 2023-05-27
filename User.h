#pragma once
#include "MyString.h"
#include "GlobalConstants.h"

//TO-DO
/*
* - consider adding setters requiring identification - password for resetting any data
* - Exception handling
*/
class User
{
private:
	MyString userName;
	MyString password;
	MyString firstName;
	MyString lastName;
	double moneyAccount = 0; //user will be able to add or pay money from the available here
	//driver will be able to accept payment in here

protected:
	int setMoneyAccount(double newAmount);

public:
	User();
	User(const char* userName, const char* password, const char* firstName, const char* lastName);
	const MyString& getUserName() const;
	void setUserName(const char* newUserName);
	void setPassword(const char* oldPassword, const char* newPassword);
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	double getMoneyAmount() const;

};

