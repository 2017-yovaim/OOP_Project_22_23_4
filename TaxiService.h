#pragma once
#include "MyVector.hpp"
#include "User.h"
#include "Client.h"
#include "Driver.h"
#include "Order.h"
#include <fstream>

class TaxiService
{
private:

	MyVector<Client> clients; 
	MyVector<Driver> drivers;
	unsigned currentClientIndex = INVALID_INDEX; //when a client logs in, this is set to the index of this user in the vector
	//it is then used as a sort of client id within the system
	unsigned currentDriverIndex = INVALID_INDEX; //same thing, but with the drivers

	MyVector<Order> orders;

	double totalProfit = 0; //records all profits collected by the drivers
	
	int findNearestDriver(const Order& order, const MyVector<unsigned>& excludedDrivers);



public:

	const MyVector<Client>& getClients() const;
	const MyVector<Driver>& getDrivers() const;
	const MyVector<Order>& getOrders() const;
	unsigned getCurrentClientIndex() const;
	unsigned getCurrentDriverIndex() const;
	double getTotalProfit() const;

	//login and register functions
	int registerClient(const MyString& userName, const MyString& password, const MyString& firstName,
		const MyString& lastName);
	int registerDriver(const MyString& userName, const MyString& password, const MyString& firstName,
		const MyString& lastName, const MyString& carNumber, const MyString& phoneNumber);
	int login(const MyString& userName, const MyString& password);
	int logout();


	//user functions
	int order(const Address& from, const Address& to, unsigned passengers);
	int checkOrder(unsigned orderID) const;
	int pay(unsigned orderID, double amount);
	int cancelOrder(unsigned orderID);
	int rate(unsigned orderID, int rating);
	int addMoney(unsigned amount);

	//driver functions
	int changeAddress(const Address& newAddress);
	int acceptOrder(unsigned orderID, unsigned minutes);
	int acceptPayment(unsigned orderID);
	int declineOrder(unsigned orderID);
	int finishOrder(unsigned orderID);
	double checkRating() const;



	std::ofstream& writeTaxiService(std::ofstream& output) const;
	std::ifstream& readTaxiService(std::ifstream& input);

};

