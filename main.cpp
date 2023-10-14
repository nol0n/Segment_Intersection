#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>

//       ↑
// используются только в тестах 

#include "Point.h"
#include "Segment.h"
#include "Service.h"
#include "TwoThreeTree.h"

double Segment::currentX  = -1;

void test1();
void test2();
void test3();
void test4();

int main()
{
	std::cout << "first test" << std::endl; test1();
	std::cout << "second test" << std::endl; test2();
	std::cout << "third test" << std::endl;	test3();
	std::cout << "fourth test" << std::endl; test4();

	return 0;
}

void test1()
{
	std::string filePathNaive = "test_naive_1" + std::string(".txt");
	std::string filePathEffective = "test_effective_1" + std::string(".txt");
	std::ofstream resultsNaive(filePathNaive);
	std::ofstream resultsEffective(filePathEffective);

	for (int i = 1; i <= 10001; i += 10)
	{
		Segment* dataSample = Service::randomSegments(i);

		auto start_time = std::chrono::high_resolution_clock::now();

		Service::intersectNaive(dataSample, i);

		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		resultsNaive << i << " " << duration.count() << std::endl;

		start_time = std::chrono::high_resolution_clock::now();

		Service::intersectEffective(dataSample, i);

		end_time = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		resultsEffective << i << " " << duration.count() << std::endl;
	}

	resultsNaive.close();
	resultsEffective.close();
}

void test2()
{
	std::string filePathNaive = "test_naive_2" + std::string(".txt");
	std::string filePathEffective = "test_effective_2" + std::string(".txt");
	std::ofstream resultsNaive(filePathNaive);
	std::ofstream resultsEffective(filePathEffective);

	for (int i = 1; i <= 10001; i += 10)
	{
		Segment* dataSample = Service::randomSegments(10003, i);

		auto start_time = std::chrono::high_resolution_clock::now();

		Service::intersectNaive(dataSample, 10003);

		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		resultsNaive << i << " " << duration.count() << std::endl;

		start_time = std::chrono::high_resolution_clock::now();

		Service::intersectEffective(dataSample, 10003);

		end_time = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		resultsEffective << i << " " << duration.count() << std::endl;
	}

	resultsNaive.close();
	resultsEffective.close();
}

void test3()
{
	std::string filePathNaive = "test_naive_3" + std::string(".txt");
	std::string filePathEffective = "test_effective_3" + std::string(".txt");
	std::ofstream resultsNaive(filePathNaive);
	std::ofstream resultsEffective(filePathEffective);

	for (int i = 1; i <= 10001; i += 10)
	{
		Segment* dataSample = Service::randomSegments(i, double(0.001));

		auto start_time = std::chrono::high_resolution_clock::now();

		Service::intersectNaive(dataSample, i);

		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		resultsNaive << i << " " << duration.count() << std::endl;

		start_time = std::chrono::high_resolution_clock::now();

		Service::intersectEffective(dataSample, i);

		end_time = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		resultsEffective << i << " " << duration.count() << std::endl;
	}

	resultsNaive.close();
	resultsEffective.close();
}

void test4()
{
	std::string filePathNaive = "test_naive_4" + std::string(".txt");
	std::string filePathEffective = "test_effective_4" + std::string(".txt");
	std::ofstream resultsNaive(filePathNaive);
	std::ofstream resultsEffective(filePathEffective);

	for (int i = 10000; i >= 100; i -= 10)
	{
		Segment* dataSample = Service::randomSegments(10000, double(1 / i));

		auto start_time = std::chrono::high_resolution_clock::now();

		Service::intersectNaive(dataSample, 10000);

		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		resultsNaive << i << " " << duration.count() << std::endl;

		start_time = std::chrono::high_resolution_clock::now();

		Service::intersectEffective(dataSample, 10000);

		end_time = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		resultsEffective << i << " " << duration.count() << std::endl;
	}

	resultsNaive.close();
	resultsEffective.close();
}