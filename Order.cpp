#include "Order.h"
#include <iostream>
using std::cout;
using std::endl;

int orderIDAssign = 1;


Order::Order(const Address& from, const Address& to, unsigned passengers) : from(from), to(to)
{
	this->orderID = orderIDAssign++;
	this->accepted = false;
	this->finished = false;
	this->passengers = passengers;
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
	this->passengers = passengers;
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
	this->passengers = passengers;
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

//the rest will be done by the system
void Order::describeOrder() const
{
	cout << "Order #" << this->getOrderID() << endl;
	cout << "Status: ";
	if (isAccepted())
	{
		cout << " accepted." << endl;
	}
	else if(isFinished())
	{
		cout << " finished." << endl;
	}
}

