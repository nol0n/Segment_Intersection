#pragma once

#include <point.hpp>

namespace obv
{
	class Segment
	{
	private:
		Point points[2];

		int CMP_POINT;
		// коэффициенты уравнения прямой y(x) = ax + b, которая задаётся двумя точками
		double a;
		double b;

		void findCoefficients();
		double calculateY(double x) const;

	public:
		enum Position
		{
			START,
			END,
		};

		static double currentX;

		Segment();
		Segment(const Point &start, const Point &end);
		Segment(const Point &start, const Point &end, Position CMP_POINT);
		Segment(const Segment &item);

		int getCmpPoint();
		static void updateCurrentX(const Segment &item);
		bool intersects(const Segment &other);

		static bool compareByX(const Segment &x, const Segment &y);

		Segment &operator=(const Segment &item);
		bool operator==(const Segment &item);
		bool operator!=(const Segment &item);

		// следующие операции производят сравнение по y(x)
		bool operator<(const Segment &item);
		bool operator<=(const Segment &item);
		bool operator>(const Segment &item);
		bool operator>=(const Segment &item);
	};
} // obv namespace
