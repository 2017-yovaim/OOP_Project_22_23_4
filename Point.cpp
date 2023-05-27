#include "Point.h"
#include <iostream>

//TO-DO
/*
* - Exception handling
*/

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
	dx < 0 ? dx = dx * -1 : dx = dx;

	double dy = rhs.getY() - lhs.getY();
	dy < 0 ? dy = dy * -1 : dy = dy;

	return sqrt(dy * dy + dx * dx);
}
