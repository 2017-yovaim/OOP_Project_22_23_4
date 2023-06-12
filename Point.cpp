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
	/*double dx = rhs.getX() - lhs.getX();
	dx < 0 ? dx = dx * -1 : dx = dx;

	double dy = rhs.getY() - lhs.getY();
	dy < 0 ? dy = dy * -1 : dy = dy;
	*/
	double dx = rhs.getX() - lhs.getX();
	std::cout << "dx = " << dx << std::endl;
	double dy = rhs.getY() - lhs.getY();
	std::cout << "dy = " << dy << std::endl;

	double result = sqrt((dy * dy) + (dx * dx));
	std::cout << "result = " << result << std::endl;
	return result;
}

//testing needed if writing will work
std::ofstream& Point::writePoint(std::ofstream& output) const
{
	int x = this->getX();
	int y = this->getY();
	output.write((const char*)&x, sizeof(x));
	output.write((const char*)&y, sizeof(y));
	return output;
}

std::ifstream& Point::readPoint(std::ifstream& input)
{
	int x, y;
	input.read((char*)&x, sizeof(x));
	input.read((char*)&y, sizeof(y));
	this->setX(x);
	this->setY(y);
	return input;
}

bool Point::operator==(const Point& other) const
{
	return this->x == other.x && this->y == other.y;
}

bool Point::operator!=(const Point& other) const
{
	return !(this->operator==(other));
}
