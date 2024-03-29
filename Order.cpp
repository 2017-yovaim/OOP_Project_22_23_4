#include "Order.h"
#include <iostream>
using std::cout;
using std::endl;

int Order::orderIDAssign = 1;


Order::Order(const Address& from, const Address& to, unsigned passengers) : from(from), to(to)
{
	this->orderID = orderIDAssign++;
	this->accepted = false;
	this->finished = false;
	this->cancelled = false;
	this->passengers = passengers;
	this->minutes = 0;
	this->cost = 0;
}

Order::Order(const char* fromName, int fromX, int fromY,
	const char* toName, int toX, int toY,
	unsigned passengers) :
	from(fromName, fromX, fromY),
	to(toName, toX, toY)
{
	this->orderID = orderIDAssign++;
	this->accepted = false;
	this->finished = false;
	this->cancelled = false;
	this->passengers = passengers;
	this->minutes = 0;
	this->cost = 0;
}

Order::Order(const char* fromName, int fromX, int fromY, const char* fromAdditionalInfo,
	const char* toName, int toX, int toY, const char* toAdditionaInfo,
	unsigned passengers) :
	from(fromName, fromX, fromY, fromAdditionalInfo),
	to(toName, toX, toY, toAdditionaInfo)
{
	this->orderID = orderIDAssign++;
	this->accepted = false;
	this->finished = false;
	this->cancelled = false;
	this->passengers = passengers;
	this->minutes = 0;
	this->cost = 0;
}

Order::Order() : from(), to()
{
	this->orderID = orderIDAssign++;
	this->accepted = false;
	this->finished = false;
	this->cancelled = false;
	this->passengers = 1;
}

int Order::getOrderID() const
{
	return this->orderID;
}

const Address& Order::getFrom() const
{
	return this->from;
}

const Address& Order::getTo() const
{
	return this->to;
}

unsigned Order::getMinutes() const
{
	return this->minutes;
}

void Order::setMinutes(unsigned minutes)
{
	this->minutes = minutes;
}

unsigned int Order::getPassengers() const
{
	return this->passengers;
}

bool Order::isAccepted() const
{
	return this->accepted;
}

bool Order::isFinished() const
{
	return this->finished;
}

bool Order::isCancelled() const
{
	return this->cancelled;
}

void Order::setDriverID(unsigned driverID)
{
	this->driverID = driverID;
}

void Order::setClientID(unsigned clientID)
{
	this->clientID = clientID;
}

unsigned Order::getDriverID() const
{
	return this->driverID;
}

unsigned Order::getClientID() const
{
	return this->clientID;
}

const MyVector<unsigned>& Order::getDeclinedBy() const
{
	return this->declinedBy;
}

double Order::getCost() const
{
	return this->cost;
}


void Order::setCost(double amount)
{
	if (amount <= 0)
		return;

	this->cost = amount;

}

void Order::accept(unsigned driverID)
{
	this->accepted = true;
	this->setDriverID(driverID);
}

void Order::decline(unsigned DriverID)
{
	this->accepted = false;
	this->declinedBy.push_back(DriverID);
}

void Order::finish()
{
	this->finished = true;
}

void Order::cancel()
{
	this->cancelled = true;
}

void Order::setOrderID(int orderID)
{
	this->orderID = orderID;
}

void Order::setFrom(const Address& from)
{
	this->from = from;
}

void Order::setTo(const Address& to)
{
	this->to = to;
}

void Order::setPassengers(unsigned passengers)
{
	this->passengers = passengers;
}

void Order::setAccepted(bool accepted)
{
	this->accepted = accepted;
}

void Order::setFinished(bool finished)
{
	this->finished = finished;
}

void Order::setCancelled(bool cancelled)
{
	this->cancelled = cancelled;
}

//what the system displays on the console. driver information will be printed by the system separately
void Order::describeOrder() const
{
	cout << "Order #" << this->getOrderID() << endl;
	cout << "From ";
	this->getFrom().describeAddress();
	cout << "To ";
	this->getTo().describeAddress();
	cout << "Status:";
	if (isCancelled())
	{
		cout << " cancelled." << endl;
	}
	else if (isFinished())
	{
		cout << " finished." << endl;
	}
	else if (isAccepted())
	{
		cout << " accepted. Estimated time: " << this->minutes << " minutes." << endl;
	}
	else
	{
		cout << " not accepted yet." << endl;
	}
}


std::ofstream& Order::writeOrder(std::ofstream& output) const
{
	int orderid = this->getOrderID();
	output.write((const char*)&orderid, sizeof(orderid));

	this->from.writeAddress(output);
	this->to.writeAddress(output);

	int tempPassengers = this->getPassengers();
	output.write((const char*)&tempPassengers, sizeof(tempPassengers));

	unsigned tempMinutes = this->getMinutes();
	output.write((const char*)&tempMinutes, sizeof(tempMinutes));

	double tempCost = this->getCost();
	output.write((const char*)&tempCost, sizeof(tempCost));

	bool boolValues = this->accepted;
	output.write((const char*)&boolValues, sizeof(boolValues));

	boolValues = this->finished;
	output.write((const char*)&boolValues, sizeof(boolValues));

	boolValues = this->cancelled;
	output.write((const char*)&boolValues, sizeof(boolValues));

	unsigned userid = this->driverID;
	output.write((const char*)&userid, sizeof(userid));

	userid = this->clientID;
	output.write((const char*)&userid, sizeof(userid));

	return output;
}

//reads order into an already existing object
std::ifstream& Order::readOrder(std::ifstream& input)
{
	int orderid = 0;
	input.read((char*)&orderid, sizeof(orderid));

	Address tempFrom("Default name", 0, 0);
	tempFrom.readAddress(input);

	Address tempTo("Default name", 0, 0);
	tempTo.readAddress(input);

	unsigned tempPassengers = 0;
	input.read((char*)&tempPassengers, sizeof(tempPassengers));

	unsigned tempMinutes = 0;
	input.read((char*)&tempMinutes, sizeof(tempMinutes));

	double tempCost = 0;
	input.read((char*)&tempCost, sizeof(tempCost));

	bool tempAccepted = false;
	input.read((char*)&tempAccepted, sizeof(tempAccepted));

	bool tempFinished = false;
	input.read((char*)&tempFinished, sizeof(tempFinished));

	bool tempCancelled = false;
	input.read((char*)&tempCancelled, sizeof(tempCancelled));

	unsigned tempDriver = INVALID_INDEX;
	input.read((char*)&tempDriver, sizeof(tempDriver));

	unsigned tempClient = INVALID_INDEX;
	input.read((char*)&tempClient, sizeof(tempClient));

	this->setOrderID(orderid);
	this->setFrom(tempFrom);
	this->setTo(tempTo);
	this->setPassengers(tempPassengers);
	this->setMinutes(tempMinutes);
	this->setCost(tempCost);
	this->setAccepted(tempAccepted);
	this->setFinished(tempFinished);
	this->setCancelled(tempCancelled);
	this->setDriverID(tempDriver);
	this->setClientID(tempClient);

	return input;
}

bool operator==(const Order& lhs, const Order& rhs)
{
	return lhs.getOrderID() == rhs.getOrderID();
}

bool operator!=(const Order& lhs, const Order& rhs)
{
	return lhs.getOrderID() != rhs.getOrderID();
}

