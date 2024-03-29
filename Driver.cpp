#include "Driver.h"

Driver::Driver() : 
	User("default_driver_username", "defaultPassword", "John", "Doe"),
	carNumber("1234A"), phoneNumber("0888888888"),
	currentAddress("Default Driver Address", 0, 0, "This is the default driver address")
{}

Driver::Driver(const char* userName, const char* password, const char* firstName, const char* lastName,
	const char* carNumber, const char* phoneNumber, const Address& currentAddress) :
	User(userName, password, firstName, lastName), 
	carNumber(carNumber), phoneNumber(phoneNumber),
	currentAddress(currentAddress) {}

Driver::Driver(const char* userName, const char* password, const char* firstName, const char* lastName,
	const char* carNumber, const char* phoneNumber) : 
	User(userName, password, firstName, lastName),
	carNumber(carNumber), phoneNumber(phoneNumber), 
	currentAddress("Default Driver Address", 0, 0, "This is the default driver address")
{}

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
	return SUCCESS;
}

double Driver::acceptPayment(double amount)
{
	if (amount <= 0) //not a valid money amount
	{
		return FAIL_TO_CHANGE_MONEY_AMOUNT;
	}

	this->setMoneyAccount(this->getMoneyAmount() + amount);
	return SUCCESS;
}

//what the user interface displays
void Driver::describeDriver() const
{
	std::cout << "Driver: " << this->getFirstName().c_str() << " " << this->getLastName().c_str() << std::endl;
	std::cout << "Car number: " << this->getCarNumber().c_str() << std::endl;
	std::cout << "Phone number: " << this->getPhoneNumber().c_str() << std::endl;
}

void Driver::checkMessages() const
{
	size_t messagesSize = this->messages.getSize();

	if (messagesSize == 0)
	{
		std::cout << "You have no messages." << std::endl;
		return;
	}

	for (size_t i = 0; i < messagesSize; i++)
	{
		this->messages[i].describeOrder();
	}
}

//the system sends a message to the driver
int Driver::pushOrder(Order& order)
{
	this->messages.push_back(order);
	return SUCCESS;
}

//the system removes a message of the driver
int Driver::removeMessage(Order& order)
{
	unsigned indexToDelete = this->messages.getIndex(order);
	this->messages.erase(indexToDelete);
	return SUCCESS;
}

//returns the average of all ratings
double Driver::getAverageRating() const
{
	if (this->numberOfRatings != 0)
		return this->sumOfAllRatings / this->numberOfRatings;
	else
		return 0;
}

void Driver::addRating(double rating)
{
	this->sumOfAllRatings += rating;
	this->numberOfRatings++;
}


std::ofstream& Driver::writeUser(std::ofstream& output) const
{
	//write driver data
	User::writeUser(output);
	this->carNumber.writeString(output);
	this->phoneNumber.writeString(output);
	this->currentAddress.writeAddress(output);

	//write ratings data
	double tempRatingsSum = this->sumOfAllRatings;
	double tempRatingsNumber = this->numberOfRatings;
	output.write((const char*)&tempRatingsSum, sizeof(tempRatingsSum));
	output.write((const char*)&tempRatingsNumber, sizeof(tempRatingsNumber));

	return output;
}

std::ifstream& Driver::readUser(std::ifstream& input)
{
	//read driver data
	User::readUser(input);
	this->carNumber.readString(input);
	this->phoneNumber.readString(input);
	this->currentAddress.readAddress(input);
	
	//read ratings data
	double tempRatingsSum = 0;
	double tempRatingsNumber = 0;

	input.read((char*)&tempRatingsSum, sizeof(tempRatingsSum));
	input.read((char*)&tempRatingsNumber, sizeof(tempRatingsNumber));

	this->sumOfAllRatings = tempRatingsSum;
	this->numberOfRatings = tempRatingsNumber;

	return input;
}

bool operator==(const Driver& lhs, const Driver& rhs)
{
	return lhs.getUserName() == rhs.getUserName() && lhs.getFirstName() == rhs.getFirstName()
		&& lhs.getCarNumber() == rhs.getCarNumber() && lhs.getPhoneNumber() == rhs.getPhoneNumber()
		&& lhs.getCurrentAddress() == rhs.getCurrentAddress();
}

bool operator!=(const Driver& lhs, const Driver& rhs)
{
	return !(lhs == rhs);
}

