#include "TaxiService.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

	//finds the nearest driver to give an order to except for those who have already refused the order
	int TaxiService::findNearestDriver(const Order& order, const MyVector<unsigned>& excludedDrivers)
	{
		double minDistance = (double)INT_MAX;
		int nearestDriverIndex = INVALID_INDEX;

		unsigned driversSize = this->drivers.getSize();
		for (unsigned i = 0; i < driversSize; i++)
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

	//checks if the currently logged in client is the one associated with a certain order
	bool TaxiService::isCorrectClient(unsigned orderID) const
	{
		return this->orders[orderID].getClientID() == this->getCurrentClientIndex();
	}

	//checks if the currently logged in driver is the one associated with a certain order
	bool TaxiService::isCorrectDriver(unsigned orderID) const
	{
		return this->orders[orderID].getDriverID() == this->getCurrentDriverIndex();
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

	double TaxiService::getTotalProfit() const
	{
		return this->totalProfit;
	}


	int TaxiService::registerClient(const MyString& userName, const MyString& password, const MyString& firstName,
		const MyString& lastName)
	{
		try
		{
			Client temp(userName.c_str(), password.c_str(), firstName.c_str(), lastName.c_str());
			this->clients.push_back(temp);
			return SUCCESS;
		}
		catch (const std::invalid_argument& iae)
		{
			return INVALID_DATA * FAIL_TO_REGISTER;
		}
		catch (const std::exception& ex)
		{
			return FAIL_TO_REGISTER;
		}
		catch (...)
		{
			return FAIL_TO_REGISTER;
		}
	}

	int TaxiService::registerDriver(const MyString& userName, const MyString& password, const MyString& firstName,
		const MyString& lastName, const MyString& carNumber, const MyString& phoneNumber)
	{
		try
		{
			Driver temp(userName.c_str(), password.c_str(), firstName.c_str(), lastName.c_str(), carNumber.c_str(), phoneNumber.c_str());
			this->drivers.push_back(temp);
			return SUCCESS;
		}

		catch (const std::invalid_argument& iae)
		{
			return INVALID_DATA * FAIL_TO_REGISTER;
		}
		catch (const std::exception& ex)
		{
			return FAIL_TO_REGISTER;
		}
		catch (...)
		{
			return FAIL_TO_REGISTER;
		}

	}

//logs a user in - looks for a match between the entered username and the entered password
int TaxiService::login(const MyString& userName, const MyString& password)
{
	if (this->currentClientIndex != INVALID_INDEX || this->currentDriverIndex != INVALID_INDEX)
	{
		return INVALID_ACTION * FAIL_TO_LOG_IN; //another user is already logged in
	}

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
	if (this->currentClientIndex == INVALID_INDEX && this->currentDriverIndex == INVALID_INDEX)
	{
		return INVALID_ACTION * FAIL_TO_LOG_OUT; //already logged out; no user signed in
	}

	this->currentClientIndex = INVALID_INDEX;
	this->currentDriverIndex = INVALID_INDEX;
	return SUCCESS;
}


int TaxiService::order(const Address& from, const Address& to, unsigned passengers)
{
	Order temp(from, to, passengers);
	temp.setClientID(currentClientIndex);

	int nearestDriverIndex = this->findNearestDriver(temp, temp.getDeclinedBy());
	if (nearestDriverIndex == INVALID_INDEX)
	{
		return FAIL_TO_COMPLETE_ORDER; //could not offer the order to any driver
	}

	this->orders.push_back(temp);
	this->drivers[nearestDriverIndex].pushOrder(temp);
	return temp.getOrderID();
}

int TaxiService::checkOrder(unsigned orderID) const
{
	if (!this->isCorrectClient(orderID)) //user was not the one who made the order
		return INVALID_ACTION * INVALID_ROLE_LOGIN;

	this->orders[orderID].describeOrder();
	if (this->orders[orderID].isAccepted() && !this->orders[orderID].isCancelled())
	{
		this->drivers[this->orders[orderID].getDriverID()].describeDriver();
	}

	return SUCCESS;
}

int TaxiService::cancelOrder(unsigned orderID)
{
	if (!this->isCorrectClient(orderID)) //user was not the one who made the order
		return INVALID_ACTION * INVALID_ROLE_LOGIN;

	//cannot cancel an order that has been finished or already cancelled
	if (this->orders[orderID].isFinished())
		return INVALID_ACTION;

	if (this->orders[orderID].isCancelled())
		return INVALID_ACTION * ORDER_CANCELLED;

	//if a driver has already accepted the order, the system notifies him by removing it from his messages
	if (this->orders[orderID].isAccepted())
	{
		this->drivers[orders[orderID].getDriverID()].removeMessage(this->orders[orderID]);
	}

	this->orders[orderID].cancel();
	return SUCCESS;
}

int TaxiService::pay(unsigned orderID, double amount)
{
	if (!this->isCorrectClient(orderID)) //user was not the one who made the order
		return INVALID_ACTION * INVALID_ROLE_LOGIN;

	//the order must already be finished in order to be paid for
	if (!this->orders[orderID].isAccepted())
	{
		return INVALID_ACTION * ORDER_NOT_ACCEPTED;
	}
	if (!this->orders[orderID].isFinished())
	{
		return INVALID_ACTION * ORDER_NOT_FINISHED;
	}

	int status = this->clients[this->orders[orderID].getClientID()].pay(orderID, amount);

	if (status != SUCCESS)
	{
		return status;
	}

	this->orders[orderID].setCost(amount);
	return status;
}

//rates a driver
int TaxiService::rate(unsigned orderID, int rating)
{
	if (!this->isCorrectClient(orderID)) //signed-in client did not make the order
		return INVALID_ACTION * INVALID_ROLE_LOGIN;

	//the order is not marked as finished yet
	if (!this->orders[orderID].isFinished())
	{
		return INVALID_ACTION * ORDER_NOT_FINISHED;
	}

	this->drivers[this->orders[orderID].getDriverID()].addRating(rating);
	return SUCCESS;
}

//adds money to client account
int TaxiService::addMoney(unsigned amount)
{
	return this->clients[currentClientIndex].addMoney(amount);
}


int TaxiService::changeAddress(const Address& newAddress)
{
	return this->drivers[currentDriverIndex].changeAddress(newAddress);
}

int TaxiService::acceptOrder(unsigned orderID, unsigned minutes)
{
	//cannot accept an already accepted, finished or cancelled order
	if (this->orders[orderID].isAccepted() || this->orders[orderID].isFinished() || this->orders[orderID].isCancelled())
	{
		return INVALID_ACTION;
	}


	this->orders[orderID].accept(this->currentDriverIndex);
	this->orders[orderID].setMinutes(minutes);
	return ORDER_ACCEPTED;
}

int TaxiService::acceptPayment(unsigned orderID)
{
	//cannot accept payment for order they have not accepted or completed or which is cancelled	
	if (!this->isCorrectDriver(orderID))
		return INVALID_ACTION * INVALID_ROLE_LOGIN * FAIL_TO_CHANGE_MONEY_AMOUNT;

	if (!this->orders[orderID].isAccepted())
		return INVALID_ACTION * ORDER_NOT_ACCEPTED;

	if (!this->orders[orderID].isFinished())
		return INVALID_ACTION * ORDER_NOT_FINISHED;

	if (this->orders[orderID].isCancelled())
		return INVALID_ACTION * ORDER_CANCELLED;

	int status = this->drivers[this->orders[orderID].getDriverID()].acceptPayment(this->orders[orderID].getCost());
	if (status != SUCCESS)
		return status;

	this->totalProfit += this->orders[orderID].getCost();
	return SUCCESS;
}



int TaxiService::declineOrder(unsigned orderID)
{
	//cannot decline an order that has already been accepted
	if (this->orders[orderID].isAccepted() || this->orders[orderID].isFinished())
		return INVALID_ACTION * INVALID_ROLE_LOGIN;

	//cannot decline a cancelled order
	if (this->orders[orderID].isCancelled())
		return INVALID_ACTION * ORDER_CANCELLED;

	//driver has already declined the order
	if (this->orders[orderID].getDeclinedBy().contains(currentDriverIndex))
		return INVALID_ACTION;
	
	//decline order and remove it from driver's messages
		this->orders[orderID].decline(this->currentDriverIndex);
		this->drivers[this->currentDriverIndex].removeMessage(this->orders[orderID]);

	//offering the order to the next closest driver who hasn't declined it yet
	int nextDriver = this->findNearestDriver(this->orders[orderID], this->orders[orderID].getDeclinedBy());
	if (nextDriver == INVALID_INDEX)
	{
		return FAIL_TO_DECLINE_ORDER * INVALID_DATA;
	}
	this->drivers[nextDriver].pushOrder(this->orders[orderID]);

	return ORDER_DECLINED;
}

int TaxiService::finishOrder(unsigned orderID)
{
	//cannot finish an order they have not accepted
	if (!this->isCorrectDriver(orderID))
		return INVALID_ACTION * INVALID_ROLE_LOGIN;

	//cannot finish a cancelled order
	if (this->orders[orderID].isCancelled())
		return INVALID_ACTION * ORDER_CANCELLED;

	//cannot finish an already finished order
	if (this->orders[orderID].isFinished())
		return INVALID_ACTION;

	//flag the order as finished, change the driver address and remove order from driver's messages
	this->orders[orderID].finish();
	this->drivers[currentDriverIndex].changeAddress(this->orders[orderID].getTo());
	this->drivers[currentDriverIndex].removeMessage(this->orders[orderID]);

	return SUCCESS;
}


double TaxiService::checkRating() const
{
	return this->drivers[currentDriverIndex].getAverageRating();
}

//current driver index and current client index will not be recorded, as they are dependent on the
//current use session of the programme and do not affect the taxi service records
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

	//same process for the orders
	int numberOfOrders = this->orders.getSize();
	output.write((const char*)&numberOfOrders, sizeof(numberOfOrders));
	for (int i = 0; i < numberOfOrders; i++)
	{
		this->orders[i].writeOrder(output);
	}

	//write the total profit
	double tempMoney = this->totalProfit;
	output.write((const char*)&tempMoney, sizeof(tempMoney));

	return output;
}

std::ifstream& TaxiService::readTaxiService(std::ifstream& input)
{
	//clear data from potential previous use
	this->clients.clear();
	this->drivers.clear();
	this->orders.clear();

	//read the clients
	int currentNumberOfClients = 0;
	input.read((char*)&currentNumberOfClients, sizeof(currentNumberOfClients));
	for (int i = 0; i < currentNumberOfClients; i++)
	{
		if (i >= this->clients.getSize())
			this->clients.push_back(Client()); //will resize
		this->clients[i].readUser(input);
	}

	//read the drivers
	int currentNumberOfDrivers = 0;
	input.read((char*)&currentNumberOfDrivers, sizeof(currentNumberOfDrivers));
	for (int i = 0; i < currentNumberOfDrivers; i++)
	{
		if (i >= this->drivers.getSize())
			this->drivers.push_back(Driver());
		this->drivers[i].readUser(input);
	}

	//read the orders
	int currentNumberOfOrders = 0;
	input.read((char*)&currentNumberOfOrders, sizeof(currentNumberOfOrders));
	for (int i = 0; i < currentNumberOfOrders; i++)
	{
		if (i >= this->orders.getSize())
			this->orders.push_back(Order());
		this->orders[i].readOrder(input);
	}

	//read the total profit
	double currentTotalProfit = 0;
	input.read((char*)&currentTotalProfit, sizeof(currentTotalProfit));
	this->totalProfit = currentTotalProfit;

	return input;
}