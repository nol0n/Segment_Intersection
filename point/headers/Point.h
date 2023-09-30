#pragma once
#include <iostream>

class Point
{
public:
	double x;
	double y;

	Point();
	Point(double x, double y);

	static bool compareByX(const Point& x, const Point& y);
	static bool compareByY(const Point& x, const Point& y);

	bool operator<(const Point& item);
	bool operator>(const Point& item);
	bool operator==(const Point& item);
	bool operator!=(const Point& item);
	bool operator<=(const Point& item);
	bool operator>=(const Point& item);
	
	Point& operator=(const Point& item);

	friend std::ostream& operator<<(std::ostream& os, const Point& point);
};