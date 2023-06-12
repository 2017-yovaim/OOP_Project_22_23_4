#include "TaxiService.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

/*
* TO-DO
* - some data validation is not accurate - fix
*/
	//finds the nearest driver except for those who have already refused the order
	int TaxiService::findNearestDriver(const Order& order, const MyVector<unsigned>& excludedDrivers)
	{
		double minDistance = (double)INT_MAX;
		int nearestDriverIndex = INVALID_INDEX;
		for (unsigned i = 0; i < this->drivers.getSize(); i++)
		{
			if (excludedDrivers.contains(i))
				continue; //one of the drivers who already refused the order
			double currentDistance = getAddressesDistance(order.getFrom(), this->drivers[i].getCurrentAddress());
			if (currentDistance < minDistance)
			{
				minDistance = currentDistance;
				nearestDriverIndex = i;
			}
		}
		return nearestDriverIndex;
	}


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
				this->isClient = false;
				this->currentClientIndex = INVALID_INDEX;
				return SUCCESS;
			}
			else
			{
				return INVALID_DATA * FAIL_TO_LOG_IN; //user has the right username but not the correct password
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
				this->isClient = true;
				this->currentDriverIndex = INVALID_INDEX;
				return SUCCESS;
			}
			else
			{
				return INVALID_DATA * FAIL_TO_LOG_IN;
			}
		}
	}

	return FAIL_TO_LOG_IN;
}

int TaxiService::logout()
{
	this->currentClientIndex = INVALID_INDEX;
	this->currentDriverIndex = INVALID_INDEX;
	this->isClient = false;
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

bool TaxiService::isSignedInAsClient() const
{
	return this->isClient;
}

const MyVector<Client>& TaxiService::getClients() const
{
	return this->clients;
}
const MyVector<Driver>& TaxiService::getDrivers() const
{
	return this->drivers;
}

const MyVector<Order>& TaxiService::getOrders() const
{
	return this->orders;
}

unsigned TaxiService::getCurrentClientIndex() const
{
	return this->currentClientIndex;
}

unsigned TaxiService::getCurrentDriverIndex() const
{
	return this->currentDriverIndex;
}

int TaxiService::order(const Address& from, const Address& to, unsigned passengers)
{
	Order temp(from, to, passengers);
	temp.setClientID(currentClientIndex);
	this->orders.push_back(temp);
	this->drivers[this->findNearestDriver(temp, temp.getDeclinedBy())].pushOrder(temp);
	return temp.getOrderID();
}

void TaxiService::checkOrder(unsigned orderID) const
{
	//if (orderID >= this->orders.getSize())
		//throw std::invalid_argument("No order with such id");

	this->orders[orderID].describeOrder();
	if (this->orders[orderID].isAccepted())
	{
		this->drivers[this->orders[orderID].getDriverID()].describeDriver();
	}
}

int TaxiService::cancelOrder(unsigned orderID)
{
	this->orders[orderID].cancel();
	return SUCCESS;
}

int TaxiService::pay(unsigned orderID, double amount)
{
	//if (orderID >= this->orders.getSize())
		//throw std::invalid_argument("No order with such id");

	if (!this->orders[orderID].isFinished() || !this->orders[orderID].isAccepted())
		throw std::logic_error("Cannot pay for an order that has not been accepted or finished.");

	return this->clients[this->orders[orderID].getClientID()].pay(orderID, amount);
}

int TaxiService::acceptPayment(unsigned orderID, double amount)
{
	//if (orderID >= this->orders.getSize())
		//throw std::invalid_argument("No order with such id");

	if (!this->orders[orderID].isFinished() || !this->orders[orderID].isAccepted())
		throw std::logic_error("Cannot accept payment for an order that has not been accepted or finished.");

	return this->drivers[this->orders[orderID].getDriverID()].acceptPayment(amount);
	this->totalProfit += amount;
}

int TaxiService::acceptOrder(unsigned orderID)
{
	this->orders[orderID].accept(this->currentDriverIndex);
	return ORDER_ACCEPTED;
}

int TaxiService::declineOrder(unsigned orderID)
{
	//decline order and remove it from driver's messages
	this->orders[orderID].decline(this->currentDriverIndex);
	this->drivers[this->currentDriverIndex].removeMessage(this->orders[orderID]);

	//offering the order to the next closest driver who hasn't declined it yet
	int nextDriver = this->findNearestDriver(this->orders[orderID], this->orders[orderID].getDeclinedBy());
	if (nextDriver == INVALID_INDEX)
	{
		return FAIL_TO_DECLINE_ORDER | INVALID_DATA;
	}
	this->drivers[nextDriver].pushOrder(this->orders[orderID]);

	return ORDER_DECLINED;
}

int TaxiService::finishOrder(unsigned orderID)
{
	//if (orderID >= this->orders.getSize())
		//throw std::invalid_argument("No order with such id");

	this->orders[orderID].finish();
	this->drivers[currentDriverIndex].changeAddress(this->orders[orderID].getTo());
	return SUCCESS;
}

std::ofstream& TaxiService::writeTaxiService(std::ofstream& output) const
{
	//write all the clients - first write how many there currently are
	int numberOfClients = this->clients.getSize();
	output.write((const char*)&numberOfClients, sizeof(numberOfClients));
	for (int i = 0; i < numberOfClients; i++)
	{
		this->clients[i].writeUser(output);
	}

	//same process for the drivers
	int numberOfDrivers = this->drivers.getSize();
	output.write((const char*)&numberOfDrivers, sizeof(numberOfDrivers));
	for (int i = 0; i < numberOfDrivers; i++)
	{
		this->drivers[i].writeUser(output);
	}

	//current driver index and current client index will not be recorded, as they are dependent on the
	//current use session of the programme and do not affect the taxi service records

	int numberOfOrders = this->orders.getSize();
	output.write((const char*)&numberOfOrders, sizeof(numberOfOrders));
	for (int i = 0; i < numberOfOrders; i++)
	{
		this->orders[i].writeOrder(output);
	}

	double tempMoney = this->totalProfit;
	output.write((const char*)&tempMoney, sizeof(tempMoney));

	return output;
}