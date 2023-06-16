#pragma once
#include "User.h"
#include "Address.h"

class Client : public User
{
	//all data for Client is in the User

public:

	Client();
	Client(const char* userName, const char* password, const char* firstName, const char* lastName);
	int addMoney(double amount); //adds money to user tab

	int pay(int orderID, double amount); //pays for order

	//bool operator==(const Client& other) const;
	//bool operator!=(const Client& other) const;

};

bool operator==(const Client& lhs, const Client& rhs);
bool operator!=(const Client& lhs, const Client& rhs);

