#pragma once
#include "MyVector.hpp"
#include "User.h"
#include "Client.h"
#include "Driver.h"
#include "Order.h"
class TaxiService
{
private:
	MyVector<Client> clients; //User?
	MyVector<Driver> drivers; //User?
	unsigned currentClientIndex = INVALID_INDEX; //when a client logs in, this is set to the index of this user in the vector
	//it is then used as a sort of client id within the system
	unsigned currentDriverIndex = INVALID_INDEX; //same thing, but with the drivers
	//since only one user can be signed at a time, a currentUserIndex might be more appropriate, but then
	//there would need to be constant checking whether the user is a client or not

	MyVector<Order> orders;

public:
	//void run();
	int login(const MyString& userName, const MyString& password);
	int logout();
	int registerClient(const MyString& userName, const MyString& password, const MyString& firstName, 
		const MyString& lastName);
	int registerDriver(const MyString& userName, const MyString& password, const MyString& firstName,
		const MyString& lastName, const MyString& carNumber, const MyString& phoneNumber);

	//user functions
	int order(const Address& from, const Address& to, unsigned passengers);
	void checkOrder(unsigned orderID) const;
	int pay(unsigned orderID, double amount);

	//driver functions
	int acceptPayment(unsigned orderID, double amount);
	int declineOrder(unsigned orderID);
	int finishOrder(unsigned orderID);




};

