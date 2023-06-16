#include "Point.h"
#include <iostream>


void Point::setX(int x)
{
	if (x < MIN_LATITUDE)
		throw std::invalid_argument("Latitude is smaller than smallest possible");
	if (x > MAX_LATITUDE)
		throw std::invalid_argument("Latitude is bigger than biggest possible");
	this->x = x;
}

void Point::setY(int y)
{
	if (y < MIN_LONGITUDE)
		throw std::invalid_argument("Longitude is smaller than smallest possible");
	if (y > MAX_LONGITUDE)
		throw std::invalid_argument("Longitude is bigger than biggest possible");
	this->y = y;
}

Point::Point() = default;

Point::Point(int x, int y)
{
	this->setX(x);
	this->setY(y);
}

int Point::getX() const
{
	return this->x;
}

int Point::getY() const
{
	return this->y;
}

double getDistance(const Point& lhs, const Point& rhs)
{
	double dx = rhs.getX() - lhs.getX();
	double dy = rhs.getY() - lhs.getY();

	double result = sqrt((dy * dy) + (dx * dx));
	return result;
}


std::ofstream& Point::writePoint(std::ofstream& output) const
{
	int x = this->getX();
	int y = this->getY();
	output.write((const char*)&x, sizeof(x));
	output.write((const char*)&y, sizeof(y));
	return output;
}

//reads each coordinate in an already built object of type Point
std::ifstream& Point::readPoint(std::ifstream& input)
{
	int x, y;
	input.read((char*)&x, sizeof(x));
	input.read((char*)&y, sizeof(y));
	this->setX(x);
	this->setY(y);
	return input;
}

//bool Point::operator==(const Point& other) const
//{
//	return this->x == other.x && this->y == other.y;
//}
//
//bool Point::operator!=(const Point& other) const
//{
//	return !(this->operator==(other));
//}

bool operator==(const Point& lhs, const Point& rhs)
{
	return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}

bool operator!=(const Point& lhs, const Point& rhs)
{
	return !(lhs == rhs);
}
