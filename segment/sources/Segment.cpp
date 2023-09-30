#include "Segment.h"

void swap(double& a, double& b)
{
	double tmp = a;
	a = b;
	b = a;
}

double min(double a, double b)
{
	return (a < b) ? a : b;
}

double max(double a, double b)
{
	return (a > b) ? a : b;
}

double area(Point a, Point b, Point c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool boundingBox(double a, double b, double c, double d) {
	if (a > b) swap(a, b);
	if (c > d) swap(c, d);
	return max(a, c) <= min(b, d);
}

Segment::Segment()
{
	points[START] = Point(0, 0);
	points[END] = Point(0, 0);
	findCoefficients();
	CMP_POINT = -1;
}

Segment::Segment(const Point& start, const Point& end)
{
	points[START] = start;
	points[END] = end;
	findCoefficients();
	CMP_POINT = -1;
}

Segment::Segment(const Point& start, const Point& end, Position POS)
{
	points[START] = start;   
	points[END] = end;
	this->CMP_POINT = POS;
	findCoefficients();
}

Segment::Segment(const Segment& item)
{
	points[START] = item.points[START];
	points[END] = item.points[END];
	a = item.a;
	b = item.b;
	CMP_POINT = item.CMP_POINT;
}

int Segment::getCmpPoint()
{
	return this->CMP_POINT;
}

void Segment::updateCurrentX(const Segment& item)
{
	currentX = item.points[item.CMP_POINT].x;
}

void Segment::findCoefficients()
{
	a = (points[END].y - points[START].y) / (points[END].x - points[START].x);
	b = points[START].y - a * points[START].x;
}

double Segment::calculateY(double x) const
{
	return (a * x + b);
}

bool Segment::intersects(const Segment& other)
{
	if (other.CMP_POINT != -1)
	{
		return (boundingBox(points[START].x, points[END].x, other.points[START].x, other.points[END].x) &&
			boundingBox(points[START].y, points[END].y, other.points[START].y, other.points[END].y) &&
			(area(points[START], points[END], other.points[START]) * area(points[START], points[END], other.points[END]) <= 0) &&
			(area(other.points[START], other.points[END], points[START]) * area(other.points[START], other.points[END], points[END]) <= 0));
	}
	else
	{
		return false;
	}
}

bool Segment::compareByX(const Segment& x, const Segment& y)
{
	return (x.points[x.CMP_POINT].x < y.points[y.CMP_POINT].x);
}

Segment& Segment::operator=(const Segment& item)
{
	if (this != &item)
	{
		this->points[START] = item.points[START];
		this->points[END]   = item.points[END];
		this->CMP_POINT     = item.CMP_POINT;
		findCoefficients();
	}
	return *this;
}

bool Segment::operator==(const Segment& item)
{
	return (this->points[START] == item.points[START] &&
			this->points[END] == item.points[END] /*&&
			this->CMP_POINT == item.CMP_POINT*/);
}

bool Segment::operator!=(const Segment& item)
{
	return !(*this == item);
}

bool Segment::operator<(const Segment& item)
{
	return (this->calculateY(currentX) < item.calculateY(currentX));
}

bool Segment::operator<=(const Segment& item)
{
	return (this->calculateY(currentX) <= item.calculateY(currentX));
}

bool Segment::operator>(const Segment& item)
{
	return (this->calculateY(currentX) > item.calculateY(currentX));
}

bool Segment::operator>=(const Segment& item)
{
	return (this->calculateY(currentX) >= item.calculateY(currentX));
}

