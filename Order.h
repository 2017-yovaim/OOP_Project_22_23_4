#pragma once
#include "Address.h"
#include <fstream>


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
	bool cancelled;

	unsigned driverID = INVALID_INDEX; //id of driver who accepts the order - managed by the system
	unsigned clientID = INVALID_INDEX; //id of client who makes the order - managed by the system
	//Order(int orderID, const Address& from, const Address& to, unsigned passengers, bool accepted, bool finished, bool cancelled,
		//unsigned driverID, unsigned clientID); 
		//for the reading from binary file

	void setOrderID(int orderID);
	void setFrom(const Address& from);
	void setTo(const Address& to);
	void setPassengers(unsigned passengers);
	void setAccepted(bool accepted);
	void setFinished(bool finished);
	bool setCancelled(bool cancelled);


public:
	//accepted and finished are set as false by default for all constructors
	Order(const Address& from, const Address& to, unsigned passengers);

	Order(const char* fromName, int fromX, int fromY,
		const char* toName, int toX, int toY,
		unsigned passengers);

	Order(const char* fromName, int fromX, int fromY, const char* fromAdditionalInfo,
		const char* toName, int toX, int toY, const char* toAdditionaInfo,
		unsigned passengers);

	int getOrderID() const;
	const Address& getFrom() const;
	const Address& getTo() const;
	unsigned int getPassengers() const;
	bool isAccepted() const;
	bool isFinished() const;
	bool isCancelled() const;

	void setDriverID(unsigned driverID);
	void setClientID(unsigned clientID);
	unsigned getDriverID() const;
	unsigned getClientID() const;

	void describeOrder() const; //basically what checkOrder displays

	//change status flags & alert system of status changes
	void accept(unsigned driverID); //sets accepted to true
	void decline(); //sets accepted to false
	void finish(); //sets finished to true
	void cancel(); //sets cancelled to true

	std::ofstream& writeOrder(std::ofstream& output) const;
	std::ifstream& readOrder(std::ifstream& input);



};


