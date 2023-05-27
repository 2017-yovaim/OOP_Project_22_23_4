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
	int order(const Address& currentAddress, const Address& destination, int passengerCount) const;
	int checkOrder(int orderID) const;
	int cancelOrder(int orderID) const;
	int rate(const MyString& driverFirstName, const MyString& driverLastName, int rating) const;

};

