#include "Address.h"

Address::Address(const char* name, int x, int y) : name(name), coordinates(x, y)
{}

Address::Address(const char* name, const Point& p) : name(name), coordinates(p) {}

Address::Address(const char* name, int x, int y, const char* additionalInfo) : name(name), coordinates(x, y),
additionalInfo(additionalInfo) {}

Address::Address(const char* name, const Point& p, const char* additionalInfo) : name(name), coordinates(p),
additionalInfo(additionalInfo) {}

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

double getAddressesDistance(const Address& lhs, const Address& rhs)
{
	return getDistance(lhs.getCoordinates(), rhs.getCoordinates());
}
