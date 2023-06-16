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
	if (amount > this->getMoneyAmount())
		return FAIL_TO_CHANGE_MONEY_AMOUNT;

	return this->setMoneyAccount(this->getMoneyAmount() - amount);
}

bool Client::operator==(const Client& other) const
{
	return this->getUserName() == other.getUserName() &&
		this->getFirstName() == other.getFirstName() && this->getLastName() == other.getLastName();
}

bool Client::operator!=(const Client& other) const
{
	return !(this->operator==(other));
}

