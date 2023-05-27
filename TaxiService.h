#pragma once
#include "MyVector.hpp"
#include "User.h"
#include "Client.h"
#include "Driver.h"
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

public:
	void run();
	int login(const MyString& userName, const MyString& password);
	int logout();

};

