#pragma once
#include "Address.h"
#include <fstream>
#include "MyVector.hpp"


class Order
{
private:

	static int orderIDAssign;

	int orderID;
	Address from;
	Address to;
	unsigned int passengers = 0;
	unsigned int minutes = 0;
	double cost = 0;
	bool accepted = false;
	bool finished = false;
	bool cancelled = false;

	unsigned driverID = INVALID_INDEX; //id of driver who accepts the order - managed by the system
	unsigned clientID = INVALID_INDEX; //id of client who makes the order - managed by the system
	MyVector<unsigned> declinedBy; //ids of drivers who've declined the offer - managed by the system

	void setOrderID(int orderID);
	void setFrom(const Address& from);
	void setTo(const Address& to);
	void setPassengers(unsigned passengers);
	void setAccepted(bool accepted);
	void setFinished(bool finished);
	void setCancelled(bool cancelled);


public:

	//accepted, finished and cancelled are set as false by default for all constructors
	Order(const Address& from, const Address& to, unsigned passengers);

	Order(const char* fromName, int fromX, int fromY,
		const char* toName, int toX, int toY,
		unsigned passengers);

	Order(const char* fromName, int fromX, int fromY, const char* fromAdditionalInfo,
		const char* toName, int toX, int toY, const char* toAdditionaInfo,
		unsigned passengers);

	Order();

	int getOrderID() const;
	const Address& getFrom() const;
	const Address& getTo() const;
	unsigned int getPassengers() const;
	double getCost() const;
	const MyVector<unsigned>& getDeclinedBy() const;
	unsigned int getMinutes() const;
	bool isAccepted() const;
	bool isFinished() const;
	bool isCancelled() const;

	void setCost(double amount);
	void setMinutes(unsigned minutes);
	void setDriverID(unsigned driverID);
	void setClientID(unsigned clientID);
	unsigned getDriverID() const;
	unsigned getClientID() const;

	void describeOrder() const; //what checkOrder displays

	//change status flags
	void accept(unsigned driverID); //sets accepted to true
	void decline(unsigned driverID); //sets accepted to false
	void finish(); //sets finished to true
	void cancel(); //sets cancelled to true

	std::ofstream& writeOrder(std::ofstream& output) const;
	std::ifstream& readOrder(std::ifstream& input);

	//bool operator==(const Order& other) const;
	//bool operator!=(const Order& other) const;



};

bool operator==(const Order& lhs, const Order& rhs);
bool operator!=(const Order& lhs, const Order& rhs);


