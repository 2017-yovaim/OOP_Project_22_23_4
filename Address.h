#pragma once
#include "MyString.h"
#include "Point.h"
#include "GlobalConstants.h"
#include <fstream>


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

	std::ofstream& writeAddress(std::ofstream& output) const; //writes address into binary file
	std::ifstream& readAddress(std::ifstream& input); //reads address from binary file

	void describeAddress() const;

};

double getAddressesDistance(const Address& lhs, const Address& rhs);
bool operator==(const Address& lhs, const Address& rhs);
bool operator!=(const Address& lhs, const Address& rhs);

