#pragma once
#include "GlobalConstants.h"
//TO-DO
/*
* Maybe data validation? Like, check max and min latitude and longitude
* and leave them in the global constants file
*
*/
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
};

