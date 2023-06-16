#include "Address.h"
#include <iostream>

Address::Address(const char* name, int x, int y) : name(name), coordinates(x, y)
{}

Address::Address(const char* name, const Point& p) : name(name), coordinates(p) {}

Address::Address(const char* name, int x, int y, const char* additionalInfo) : name(name), coordinates(x, y),
additionalInfo(additionalInfo) {}

Address::Address(const char* name, const Point& p, const char* additionalInfo) : name(name), coordinates(p),
additionalInfo(additionalInfo) {}

Address::Address() : coordinates(), name("default address name"), additionalInfo("default address add info") {}

const MyString& Address::getName() const
{
	return this->name;
}

const Point& Address::getCoordinates() const
{
	return this->coordinates;
}

int Address::getX() const
{
	return this->coordinates.getX();
}

int Address::getY() const
{
	return this->coordinates.getY();
}

const MyString& Address::getAdditionalInfo() const
{
	return this->additionalInfo;
}

//distance between address coordinates
double getAddressesDistance(const Address& lhs, const Address& rhs)
{
	return getDistance(lhs.getCoordinates(), rhs.getCoordinates());
}

//writes first the name then the coordinates then the additional info
std::ofstream& Address::writeAddress(std::ofstream& output) const
{
	this->name.writeString(output);
	this->coordinates.writePoint(output);
	this->additionalInfo.writeString(output);
	
	return output;
}

//reads the address into an already existing object
std::ifstream& Address::readAddress(std::ifstream& input)
{
	this->name.readString(input);
	this->coordinates.readPoint(input);
	this->additionalInfo.readString(input);

	return input;
}

//describes address for the console interface
void Address::describeAddress() const
{
	std::cout << this->getName().c_str() << " " << this->getX() << " " << this->getY() << " ";

	if (strcmp(this->getAdditionalInfo().c_str(), DEFAULT_EMPTY_ADD_INFO))
	{
		std::cout << this->getAdditionalInfo().c_str();
	}

	std::cout << std::endl;
}

//bool Address::operator==(const Address& other) const
//{
//	return this->name == other.name && this->coordinates == other.coordinates && this->additionalInfo == other.additionalInfo;
//}
//
//bool Address::operator!=(const Address& other) const
//{
//	return !(this->operator==(other));
//}

bool operator==(const Address& lhs, const Address& rhs)
{
	return lhs.getName() == rhs.getName() && lhs.getCoordinates() == rhs.getCoordinates() &&
		lhs.getAdditionalInfo() == rhs.getAdditionalInfo();
}

bool operator!=(const Address& lhs, const Address& rhs)
{
	return !(lhs == rhs);
}