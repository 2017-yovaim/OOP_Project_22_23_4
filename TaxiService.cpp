#include "TaxiService.h"

int TaxiService::login(const MyString& userName, const MyString& password)
{
	size_t sizeOfDrivers = this->drivers.getSize();
	for (size_t i = 0; i < sizeOfDrivers; i++)
	{
		if (this->drivers[i].getUserName() == userName)
		{
			if (this->drivers[i].isCorrectPassword(password))
			{
				this->currentDriverIndex = i;
				this->currentClientIndex = INVALID_INDEX;
				return SUCCESS;
			}
			else
			{
				return INVALID_DATA | FAIL_TO_LOG_IN; //user has the right username but not the correct password
			}
		}
	}

	size_t sizeOfClients = this->clients.getSize();
	for (size_t i = 0; i < sizeOfClients; i++)
	{
		if (this->clients[i].getUserName() == userName)
		{
			if (this->clients[i].isCorrectPassword(password))
			{
				this->currentClientIndex = i;
				this->currentDriverIndex = INVALID_INDEX;
				return SUCCESS;
			}
			else
			{
				return INVALID_DATA | FAIL_TO_LOG_IN;
			}
		}
	}

	return FAIL_TO_LOG_IN;
}

int TaxiService::logout()
{
	this->currentClientIndex = INVALID_INDEX;
	this->currentDriverIndex = INVALID_INDEX;
	return SUCCESS;
}

int TaxiService::registerClient(const MyString& userName, const MyString& password, const MyString& firstName,
	const MyString& lastName)
{
	Client temp(userName.c_str(), password.c_str(), firstName.c_str(), lastName.c_str());
	this->clients.push_back(temp);
	return SUCCESS;
}

int TaxiService::registerDriver(const MyString& userName, const MyString& password, const MyString& firstName,
	const MyString& lastName, const MyString& carNumber, const MyString& phoneNumber)
{
	Driver temp(userName.c_str(), password.c_str(), firstName.c_str(), lastName.c_str(), carNumber.c_str(), phoneNumber.c_str());
	this->drivers.push_back(temp);
	return SUCCESS;
}
