#pragma once
#include "Point.h"

class Segment
{
private:
	void findCoefficients();
	double calculateY(double x) const;
public:
	enum Position 
	{ 
		START, 
		END, 
	};

	Point points[2];
	int CMP_POINT;

	// ������������ ��������� ������  y(x) = ax + b, ������� �������� ����� �������
	double a;
	double b;
	static double currentX;

	Segment();
	Segment(const Point& start, const Point& end);
	Segment(const Point& start, const Point& end, Position CMP_POINT);
	Segment(const Segment& item);

	bool intersects(const Segment& other);

	static bool compareByX(const Segment& x, const Segment& y);

	Segment& operator=(const Segment& item);
	bool operator==(const Segment& item);
	bool operator!=(const Segment& item);

	// ��������� �������� ���������� ��������� �� y(x)
	bool operator<(const Segment& item);
	bool operator<=(const Segment& item);
	bool operator>(const Segment& item);
	bool operator>=(const Segment& item);
};