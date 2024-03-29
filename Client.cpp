#include "Client.h"

Client::Client() : Client("default_client_username", "defaultPassword", "Jean", "Doe")
{}

Client::Client(const char* userName, const char* password, const char* firstName, const char* lastName) :
	User(userName, password, firstName, lastName) {}


int Client::addMoney(double amount)
{
	return this->setMoneyAccount(this->getMoneyAmount() + amount);
}

int Client::pay(int orderID, double amount)
{
	if (amount > this->getMoneyAmount()) //not enough money in user account
		return FAIL_TO_CHANGE_MONEY_AMOUNT;

	return this->setMoneyAccount(this->getMoneyAmount() - amount);
}

bool operator==(const Client& lhs, const Client& rhs)
{
	return lhs.getUserName() == rhs.getUserName() && lhs.getFirstName() == rhs.getFirstName() && lhs.getLastName() == rhs.getLastName();
}
bool operator!=(const Client& lhs, const Client& rhs)
{
	return !(lhs == rhs);
}

