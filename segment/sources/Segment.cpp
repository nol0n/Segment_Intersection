#include "Service.h"
#include "Segment.h"

double area(Point a, Point b, Point c) {
	return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
}

bool boundingBox(double a, double b, double c, double d) {
	if (a > b) Service::swap(a, b);
	if (c > d) Service::swap(c, d);
	return Service::max(a, c) <= Service::min(b, d);
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
	currentX = item.points[item.CMP_POINT].getX();
}

void Segment::findCoefficients()
{
	a = (points[END].getY() - points[START].getY()) / (points[END].getX() - points[START].getX());
	b = points[START].getY() - a * points[START].getY();
}

double Segment::calculateY(double x) const
{
	return (a * x + b);
}

bool Segment::intersects(const Segment& other)
{
	if (other.CMP_POINT != -1)
	{
		return (boundingBox(points[START].getX(), points[END].getX(), other.points[START].getX(), other.points[END].getX()) &&
			boundingBox(points[START].getY(), points[END].getY(), other.points[START].getY(), other.points[END].getY()) &&
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
	return (x.points[x.CMP_POINT].getX() < y.points[y.CMP_POINT].getX());
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

