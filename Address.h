#pragma once
#include "MyString.h"
#include "Point.h"
#include <fstream>

//T0-DO
/*
* - friend functions for comparing two addresses and calculating the distance between them
* - Decide whether you need setters or not
*/
class Address
{
private:
	MyString name;
	Point coordinates;
	MyString additionalInfo;

public:
	Address(const char* name, int x, int y);
	Address(const char* name, const Point& p);
	Address(const char* name, int x, int y, const char* additionalInfo);
	Address(const char* name, const Point& p, const char* additionalInfo);
	Address();
	const MyString& getName() const;
	const Point& getCoordinates() const;
	int getX() const;
	int getY() const;
	const MyString& getAdditionalInfo() const;

	friend double getAddressesDistance(const Address& lhs, const Address& rhs);
	std::ofstream& writeAddress(std::ofstream& output) const;
	std::ifstream& readAddress(std::ifstream& input);

	bool operator==(const Address& other) const;
	bool operator!=(const Address& other) const;

};

