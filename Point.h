#pragma once
#include <fstream>

class Point
{
private:

	int x = 0;
	int y = 0;

public:

	Point();
	Point(int x, int y);

	void setX(int x);
	void setY(int y);

	int getX() const;
	int getY() const;

	std::ofstream& writePoint(std::ofstream& output) const; //writes a point in binary file
	std::ifstream& readPoint(std::ifstream& input); //reads a point from binary file

};

double getDistance(const Point& lhs, const Point& rhs);
bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);

