#pragma once
#include "Address.h"

//TO-DO
/*
* - Decide if you need setters (order is not expected to be altered after being made - aside from status flags)
* - Decide if you need a cancel status flag (bool cancelled)
*/



class Order
{
private:
	static int orderIDAssign;
	int orderID;
	Address from;
	Address to;
	unsigned int passengers;
	bool accepted;
	bool finished;

public:
	//accepted and finished are set as false by default for all constructors
	Order(const Address& from, const Address& to, unsigned passengers);

	Order(const char* fromName, int fromX, int fromY,
		const char* toName, int toX, int toY,
		unsigned passengers);

	Order(const char* fromName, int fromX, int fromY, const char* fromAdditionalInfor,
		const char* toName, int toX, int toY, const char* toAdditionaInfor,
		unsigned passengers);

	int getOrderID() const;
	const Address& getFrom() const;
	const Address& getTo() const;
	unsigned int getPassengers() const;
	bool isAccepted() const;
	bool isFinished() const;

	//change status flags & alert system of status changes
	void accept(); //sets accepted to true
	void decline(); //sets accepted to false
	void finish(); //sets finished to true
	void cancel();



};


