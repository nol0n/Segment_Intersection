#include <point.hpp>

namespace obv
{
	Point::Point()
	{
		x = -1;
		y = -1;
	}

	Point::Point(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	bool Point::compareByX(const Point &x, const Point &y)
	{
		return (x.x < y.x);
	}

	bool Point::compareByY(const Point &x, const Point &y)
	{
		return (x.y < y.y);
	}

	double Point::getX() const
	{
		return x;
	}

	double Point::getY() const
	{
		return y;
	}

	bool Point::operator<(const Point &item)
	{
		return this->y < item.y;
	}

	bool Point::operator>(const Point &item)
	{
		return this->y > item.y;
	}

	bool Point::operator==(const Point &item)
	{
		return (this->y == item.y && this->x == item.x);
	}

	bool Point::operator!=(const Point &item)
	{
		return !(*this == item);
	}

	bool Point::operator<=(const Point &item)
	{
		return this->y <= item.y;
	}

	bool Point::operator>=(const Point &item)
	{
		return this->y >= item.y;
	}

	Point &Point::operator=(const Point &item)
	{
		if (&item != this)
		{
			this->x = item.x;
			this->y = item.y;
		}
		return *this;
	}

	std::ostream &operator<<(std::ostream &os, const Point &point)
	{
		os << point.x << " " << point.y;
		return os;
	}
} // obv namespace
