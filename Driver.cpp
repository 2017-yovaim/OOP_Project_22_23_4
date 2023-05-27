#include "Driver.h"

Driver::Driver() : User("default_driver_username", "defaultPassword", "John", "Doe"),
carNumber("1234A"), phoneNumber("0888888888"),
currentAddress("Default Driver Address", 0, 0, "This is the default driver address")
{}

Driver::Driver(const char* userName, const char* password, const char* firstName, const char* lastName,
	const char* carNumber, const char* phoneNumber, const Address& currentAddress) :
	User(userName, password, firstName, lastName), carNumber(carNumber), phoneNumber(phoneNumber),
	currentAddress(currentAddress) {}

const MyString& Driver::getCarNumber() const
{
	return this->carNumber;
}

const MyString& Driver::getPhoneNumber() const
{
	return this->phoneNumber;
}
const Address& Driver::getCurrentAddress() const
{
	return this->currentAddress;
}

int Driver::changeAddress(const Address& newAddress)
{
	this->currentAddress = newAddress;
}

double Driver::acceptPayment(double amount)
{
	if (amount <= 0)
	{
		return FAIL_TO_CHANGE_MONEY_AMOUNT;
	}
	this->setMoneyAccount(this->getMoneyAmount() + amount);
	return SUCCESS;
}

