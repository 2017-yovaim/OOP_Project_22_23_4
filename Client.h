#pragma once
#include "User.h"
#include "Address.h"

//TO-DO
/*
* - improve consistency - sometimes you use const char (star), other times - MyString
*/


class Client : public User
{
	//all data for Client is in the User

public:

	Client();
	Client(const char* userName, const char* password, const char* firstName, const char* lastName);
	int addMoney(double amount); //adds money to user tab

	int pay(int orderID, double amount); //pays for order

	bool operator==(const Client& other) const;
	bool operator!=(const Client& other) const;

};

