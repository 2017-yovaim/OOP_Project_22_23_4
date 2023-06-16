#pragma once
#include "MyString.h"
#include "GlobalConstants.h"
#include <fstream>


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
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	double getMoneyAmount() const;

	void setUserName(const char* newUserName);
	void setPassword(const char* oldPassword, const char* newPassword);
	bool isCorrectPassword(const MyString& password) const; //checks if a password is correct for the user


	virtual std::ofstream& writeUser(std::ofstream& output) const;
	virtual std::ifstream& readUser(std::ifstream& input);


	virtual ~User() = default;
};

