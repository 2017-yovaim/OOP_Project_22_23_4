#include "User.h"


User::User() : User("default_user_name", "defaultPassword", "John", "Doe") {}

User::User(const char* userName, const char* password, const char* firstName, const char* lastName) : 
	userName(userName), password(password), firstName(firstName), lastName(lastName)

{}

const MyString& User::getUserName() const
{
	return this->userName;
}

void User::setUserName(const char* newUserName)
{
	this->userName = newUserName;
}

void User::setPassword(const char* oldPassword, const char* newPassword)
{
	if (oldPassword != this->password) //password doesn't match the old password
		return; 

	this->password = newPassword;
}

const MyString& User::getFirstName() const
{
	return this->firstName;
}

const MyString& User::getLastName() const
{
	return this->lastName;
}

double User::getMoneyAmount() const
{
	return this->moneyAccount;
}

int User::setMoneyAccount(double newAmount)
{
	if (newAmount < 0)
	{
		return (INVALID_DATA * FAIL_TO_CHANGE_MONEY_AMOUNT);
	}
	
	this->moneyAccount = newAmount;
	return SUCCESS;

}

bool User::isCorrectPassword(const MyString& password) const
{
	return this->password == password;
}

std::ofstream& User::writeUser(std::ofstream& output) const
{
	this->userName.writeString(output);
	this->password.writeString(output);
	this->firstName.writeString(output);
	this->lastName.writeString(output);

	double tempMoney = this->getMoneyAmount();
	output.write((const char*)&tempMoney, sizeof(tempMoney));

	return output;
}

//reads data from binary file into an already built object
std::ifstream& User::readUser(std::ifstream& input)
{
	this->userName.readString(input);
	this->password.readString(input);
	this->firstName.readString(input);
	this->lastName.readString(input);

	double tempMoney = 0;
	input.read((char*)&tempMoney, sizeof(tempMoney));
	this->setMoneyAccount(tempMoney);

	return input;
}


