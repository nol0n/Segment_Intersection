#include <service.hpp>

#include "TwoThreeTree.hpp"

namespace obv
{
	/// @brief проверка наличия пересечения в множестве отрезков, путем полного перебора
	/// @param segmentsArray массив из отрезков 
	/// @param arrSize размер массива 
	/// @return найдено ли пересечение
	bool Service::intersectNaive(Segment *segmentsArray, size_t arrSize)
	{
		int size = arrSize * 2;

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
			if (intersect)
				break;
		}
		return intersect;
	}

	/// @brief проверка наличия пересечения в множестве отрезков, методом секущих плоскостей
	/// @param segmentsArray массив из отрезков 
	/// @param arrSize размер массива 
	/// @return найдено ли пересечение
	bool Service::intersectEffective(Segment *segmentsArray, size_t arrSize)
	{
		int size = arrSize * 2;

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
				if (intersect)
					break;
				intersect = segmentsArray[i].intersects(tree.findSuccessor(segmentsArray[i]));
				if (intersect)
					break;
			}
			else if (segmentsArray[i].getCmpPoint() == Segment::END)
			{
				intersect = tree.findPredecessor(segmentsArray[i]).intersects(tree.findSuccessor(segmentsArray[i]));
				if (intersect)
					break;
				tree.remove(segmentsArray[i]);
			}
		}

		return intersect;
	}

	/// @brief проверка пересекается ли отрезок с каким-то из множества, используется при генерации тестовых множеств
	/// @param segmentsArray 
	/// @param arrSize 
	/// @param segment 
	/// @return 
	bool Service::intersect(Segment *segmentsArray, size_t arrSize, Segment &segment)
	{
		bool intersect = false;
		for (int i = 0; i < arrSize; i += 2)
		{
			if (segment.intersects(segmentsArray[i]))
			{
				intersect = true;
				break;
			}
		}
		return intersect;
	}

	/// @brief создание случайных значений точек
	/// @param x1 
	/// @param x2 
	/// @param y1 
	/// @param y2 
	void generatePointsRand(double &x1, double &x2, double &y1, double &y2)
	{
		x1 = (double)rand() / RAND_MAX;
		x2 = (double)rand() / RAND_MAX;
		y1 = (double)rand() / RAND_MAX;
		y2 = (double)rand() / RAND_MAX;
	}

	/// @brief создается массив отрезков путем задания случайных коордиант точек, они могут пересекаться
	/// @param size 
	/// @return массив отрезков
	Segment *Service::randomSegments(size_t size)
	{
		Segment *SegmentsArray = new Segment[size * 2]();

		std::srand((unsigned int)std::time(nullptr));

		for (int i = 0; i < size; ++i)
		{
			double x1, x2, y1, y2;
			generatePointsRand(x1, x2, y1, y2);
			if (x2 < x1)
				swap(x2, x1);

			SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
			SegmentsArray[i * 2 + 1] = Segment(Point(x1, y1), Point(x2, y2), Segment::END);
		}

		return SegmentsArray;
	}

	/// @brief создаётся массив отрезков, заданием случайных коордиант, но пересекаться будет только K и K + 1 отрезки
	/// @param size 
	/// @param K 
	/// @return массив отрезков
	Segment *Service::randomSegments(size_t size, int K)
	{
		Segment *SegmentsArray = new Segment[size * 2]();

		std::srand((unsigned int)std::time(nullptr));

		for (int i = 0; i < size; ++i)
		{
			double x1, x2, y1, y2;

			generatePointsRand(x1, x2, y1, y2);
			if (x2 < x1)
				swap(x2, x1);

			SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);

			if (i == K)
			{
				while (!SegmentsArray[i * 2].intersects(SegmentsArray[(i - 1) * 2]) ||
					   intersect(SegmentsArray, i * 2 - 2, SegmentsArray[i * 2]))
				{
					generatePointsRand(x1, x2, y1, y2);
					if (x2 < x1)
						swap(x2, x1);

					SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
				}
			}
			else
			{
				while (intersect(SegmentsArray, i * 2, SegmentsArray[i * 2]))
				{
					generatePointsRand(x1, x2, y1, y2);
					if (x2 < x1)
						swap(x2, x1);

					SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
				}
			}

			SegmentsArray[i * 2 + 1] = Segment(Point(x1, y1), Point(x2, y2), Segment::END);
		}

		return SegmentsArray;
	}

	/// @brief задание точек для случайного отрезка заданного радиуса
	/// @param x1 
	/// @param x2 
	/// @param y1 
	/// @param y2 
	/// @param radius 
	void generatePointsRandWithRadius(double &x1, double &x2, double &y1, double &y2, double radius)
	{
		double x_center = (double)rand() / RAND_MAX;
		double y_center = (double)rand() / RAND_MAX;
		double angle = M_PI * (double)rand() / RAND_MAX;

		x1 = x_center - radius * std::cos(angle) / 2.0;
		x2 = x_center + radius * std::cos(angle) / 2.0;
		y1 = y_center - radius * std::sin(angle) / 2.0;
		y2 = y_center + radius * std::sin(angle) / 2.0;
	}

	/// @brief создание массива отрезков с заданной длиной отрезка
	/// @param size 
	/// @param radius 
	/// @return массив отрезков
	Segment *Service::randomSegments(size_t size, double radius)
	{
		Segment *SegmentsArray = new Segment[size * 2]();

		std::srand((unsigned int)std::time(nullptr));

		for (int i = 0; i < size; ++i)
		{
			double x1, x2, y1, y2;
			generatePointsRandWithRadius(x1, x2, y1, y2, radius);
			if (x2 < x1)
				swap(x2, x1);

			SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
			SegmentsArray[i * 2 + 1] = Segment(Point(x1, y1), Point(x2, y2), Segment::END);
		}

		return SegmentsArray;
	}
} // obv namespace
