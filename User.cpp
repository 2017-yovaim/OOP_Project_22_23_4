#include "User.h"


User::User() : User("default_user_name", "defaultPassword", "John", "Doe") {}
User::User(const char* userName, const char* password, const char* firstName, const char* lastName)
{
	if (userName == nullptr || strlen(userName) == 0)
		throw std::invalid_argument("Invalid userName in User constructor");
	if (password == nullptr || strlen(password) == 0)
		throw std::invalid_argument("Invalid password in User constructor");
	if (firstName == nullptr || strlen(firstName) == 0)
		throw std::invalid_argument("Invalid first name in User constructor");
	if (lastName == nullptr || strlen(lastName) == 0)
		throw std::invalid_argument("Invalid last name in User constructor");

	this->userName = userName;
	this->password = password;
	this->firstName = firstName;
	this->lastName = lastName;
}

const MyString& User::getUserName() const
{
	return this->userName;
}
void User::setUserName(const char* newUserName)
{
	if (newUserName == nullptr || strlen(newUserName) == 0)
		throw std::invalid_argument("Invalid new user name is User userName setter");

	this->userName = newUserName;
}
void User::setPassword(const char* oldPassword, const char* newPassword)
{
	if (oldPassword != this->password)
		return; //password doesn't match the old password

	if (newPassword == nullptr || strlen(newPassword) == 0)
		throw std::invalid_argument("Invalid new password in User password setter");
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
		return (INVALID_DATA | FAIL_TO_CHANGE_MONEY_AMOUNT);

	this->moneyAccount = newAmount;

}

bool User::isCorrectPassword(const MyString& password) const
{
	return this->password == password;
}
