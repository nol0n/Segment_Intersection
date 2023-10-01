#include "Service.h"

bool Service::intersectNaive(Segment* segmentsArray, size_t size_)
{
	int size = size_ * 2;

	bool intersect = false;
	for (int i = 0; i < size - 1; i += 2)
	{
		for (int j = i + 2; j < size - 1; j += 2)
		{
			if (segmentsArray[i].intersects(segmentsArray[j]))
			{
				intersect = true;
				break;
			}
		}
		if (intersect) break;
	}
	return intersect;
}

bool Service::intersectEffective(Segment* segmentsArray, size_t size_)
{
	int size = size_ * 2;
	
	bool intersect = false;
	
	TwoThreeTree<Segment> tree;

	Service::sort(segmentsArray, 0, size - 1, Segment::compareByX);

	for (int i = 0; i < size; i++)
	{
		Segment::updateCurrentX(segmentsArray[i]);

		if (segmentsArray[i].getCmpPoint() == Segment::START)
		{
			tree.insert(segmentsArray[i]);
			intersect = segmentsArray[i].intersects(tree.findPredecessor(segmentsArray[i]));
			if (intersect) break;
			intersect = segmentsArray[i].intersects(tree.findSuccessor(segmentsArray[i]));
			if (intersect) break;
		}
		else if (segmentsArray[i].getCmpPoint() == Segment::END)
		{
			intersect = tree.findPredecessor(segmentsArray[i]).intersects(tree.findSuccessor(segmentsArray[i]));
			if (intersect) break;
			tree.remove(segmentsArray[i]);
		}
	}

	return intersect;
}

bool Service::intersect(Segment* segmentsArray, size_t size, Segment& segment)
{
	bool intersect = false;
	for (int i = 0; i < size; i += 2)
	{
		if (segment.intersects(segmentsArray[i]))
		{
			intersect = true;
			break;
		}
	}
	return intersect;
}

void generatePoints1(double& x1, double& x2, double& y1, double& y2)
{
	x1 = (double)rand() / RAND_MAX;
	x2 = (double)rand() / RAND_MAX;
	y1 = (double)rand() / RAND_MAX;
	y2 = (double)rand() / RAND_MAX;
}

Segment* Service::randomSegments(size_t size)
{
	Segment* SegmentsArray = new Segment[size * 2]();

	std::srand((unsigned int)std::time(nullptr));

	for (int i = 0; i < size; ++i)
	{
		double x1, x2, y1, y2;
		generatePoints1(x1, x2, y1, y2);
		if (x2 < x1) swap(x2, x1);

		SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
		SegmentsArray[i * 2 + 1] = Segment(Point(x1, y1), Point(x2, y2), Segment::END);
	}

	return SegmentsArray;
}

Segment* Service::randomSegments(size_t size, int K)
{
	Segment* SegmentsArray = new Segment[size * 2]();

	std::srand((unsigned int)std::time(nullptr));

	for (int i = 0; i < size; ++i)
	{
		double x1, x2, y1, y2;
		
		generatePoints1(x1, x2, y1, y2);
		if (x2 < x1) swap(x2, x1);

		SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
		
		if (i == K)
		{
			while (!SegmentsArray[i * 2].intersects(SegmentsArray[(i - 1) * 2]) || 
				intersect(SegmentsArray, i * 2 - 2, SegmentsArray[i * 2]))
			{
				generatePoints1(x1, x2, y1, y2);
				if (x2 < x1) swap(x2, x1);

				SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
			}
		}
		else 
		{
			while (intersect(SegmentsArray, i * 2, SegmentsArray[i * 2]))
			{
				generatePoints1(x1, x2, y1, y2);
				if (x2 < x1) swap(x2, x1);

				SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
			}
		}

		SegmentsArray[i * 2 + 1] = Segment(Point(x1, y1), Point(x2, y2), Segment::END);
	}

	return SegmentsArray;
}

void generatePoints2(double& x1, double& x2, double& y1, double& y2, double radius)
{
	double x_center = (double)rand() / RAND_MAX;
	double y_center = (double)rand() / RAND_MAX;
	double angle = M_PI * (double)rand() / RAND_MAX;

	x1 = x_center - radius * std::cos(angle) / 2.0;
	x2 = x_center + radius * std::cos(angle) / 2.0;
	y1 = y_center - radius * std::sin(angle) / 2.0;
	y2 = y_center + radius * std::sin(angle) / 2.0;
}

Segment* Service::randomSegments(size_t size, double radius)
{
	Segment* SegmentsArray = new Segment[size * 2]();

	std::srand((unsigned int)std::time(nullptr));

	for (int i = 0; i < size; ++i)
	{
		double x1, x2, y1, y2;
		generatePoints2(x1, x2, y1, y2, radius);
		if (x2 < x1) swap(x2, x1);
		
		SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
		SegmentsArray[i * 2 + 1] = Segment(Point(x1, y1), Point(x2, y2), Segment::END);
	}

	return SegmentsArray;
}