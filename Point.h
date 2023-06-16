#pragma once
#include "GlobalConstants.h"
#include <fstream>

class Point
{
private:

	int x = 0; //latitude
	int y = 0; //longitude 

public:

	Point();
	Point(int x, int y);
	void setX(int x);
	void setY(int y);
	int getX() const;
	int getY() const;

	friend double getDistance(const Point& lhs, const Point& rhs);
	std::ofstream& writePoint(std::ofstream& output) const; //writes a point in binary file
	std::ifstream& readPoint(std::ifstream& input); //reads a point from binary file

	bool operator==(const Point& other) const;
	bool operator!=(const Point& other) const;
};

