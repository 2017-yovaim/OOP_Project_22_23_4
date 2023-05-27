#pragma once
#include "User.h"
#include "Address.h"
class Driver : public User
{
private:
	MyString carNumber;
	MyString phoneNumber;
	Address currentAddress;

public:
	Driver();
	Driver(const char* userName, const char* password, const char* firstName, const char* lastName,
		const char* carNumber, const char* phoneNumber, const Address& currentAddress);
	const MyString& getCarNumber() const;
	const MyString& getPhoneNumber() const;
	const Address& getCurrentAddress() const;
	int changeAddress(const Address& newAddress);

	void checkMessages() const;
	int acceptOrder(int orderID, int minutes); //const?
	int declineOrder(int orderID); //const?
	int finishorder(int orderID); //definitely not const - changes the current address
	double acceptPayment(double amount);
};

