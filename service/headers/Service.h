#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
#include <ctime>

#include "TwoThreeTree.h"
#include "Point.h"
#include "Segment.h"

class Service
{
public:
	static bool intersectNaive(Segment* segmentsArray, size_t size);
	static bool intersectEffective(Segment* segmentsArray, size_t size);

	template <typename T>
	static void sort(T* arr, int low, int high, bool (*comp)(const T&, const T&));
	template <typename T>
	static void swap(T& x, T& y);
	template <typename T>
	static T min(T& x, T& y);
	template <typename T>
	static T max(T& x, T& y);

	static Segment* randomSegments(size_t size);
	static Segment* randomSegments(size_t size, int K);
	static Segment* randomSegments(size_t size, double radius);
private:
	static bool intersect(Segment* segmentsArray, size_t size, Segment& segment);
};

template <typename T>
void Service::swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

template <typename T>
T Service::min(T& x, T& y)
{
	return (x < y) ? x : y;
}

template <typename T>
T Service::max(T& x, T& y)
{
	return (x > y) ? x : y;
}

template <typename T>
int partition(T* arr, int low, int high, T pivot, bool (*comp)(const T&, const T&))
{
	int i = low;
	int j = low;

	while (i <= high)
	{
		if (comp(pivot, arr[i]))
		{
			i++;
		}
		else
		{
			Service::swap(arr[i], arr[j]);
			i++;
			j++;
		}
	}
	return j - 1;
}

template<typename T>
void Service::sort(T* arr, int low, int high, bool (*comp)(const T&, const T&))
{
	if (low < high)
	{
		T pivot = arr[high];
		int position = partition(arr, low, high, pivot, comp);

		sort(arr, low, position - 1, comp);
		sort(arr, position + 1, high, comp);
	}
}