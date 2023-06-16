#pragma once
#include "User.h"
#include "Address.h"
#include "MyVector.hpp"
#include "Order.h"
class Driver : public User
{
private:

	MyString carNumber;
	MyString phoneNumber;
	Address currentAddress;
	MyVector<Order> messages;

	//for rating functionality
	double sumOfAllRatings = 0;
	double numberOfRatings = 0;

public:

	Driver();
	Driver(const char* userName, const char* password, const char* firstName, const char* lastName,
		const char* carNumber, const char* phoneNumber, const Address& currentAddress);
	Driver(const char* userName, const char* password, const char* firstName, const char* lastName,
		const char* carNumber, const char* phoneNumber);

	const MyString& getCarNumber() const;
	const MyString& getPhoneNumber() const;
	const Address& getCurrentAddress() const;
	int changeAddress(const Address& newAddress);

	//when the driver receives a message, the system pushed it here
	//if the driver declines an order, the system removes it
	int pushOrder(Order& order);
	int removeMessage(Order& order);

	void checkMessages() const;
	double acceptPayment(double amount);
	double getAverageRating() const;
	void addRating(double rating);

	void describeDriver() const;

	virtual std::ofstream& writeUser(std::ofstream& output) const override;
	virtual std::ifstream& readUser(std::ifstream& input) override;

	//bool operator==(const Driver& other) const;
	//bool operator!=(const Driver& other) const;
};

bool operator==(const Driver& lhs, const Driver& rhs);
bool operator!=(const Driver & lhs, const Driver & rhs);

