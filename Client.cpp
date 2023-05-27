#include "Client.h"

Client::Client() : Client("default_client_username", "defaultPassword", "Jean", "Doe")
{}
Client::Client(const char* userName, const char* password, const char* firstName, const char* lastName) :
	User(userName, password, firstName, lastName) {}
int Client::addMoney(double amount)
{
	this->setMoneyAccount(this->getMoneyAmount() + amount);
}

int Client::pay(int orderID, double amount)
{
	this->setMoneyAccount(this->getMoneyAmount() - amount);
}

