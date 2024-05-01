#pragma once

#include <fstream>
#include <string>
#include <chrono>
#include <ctime>

#include <point.hpp>
#include <segment.hpp>
#include <service.hpp>

#define TEST_SIZE 2000

double obv::Segment::currentX = -1;

void test1()
{
	std::string filePathNaive = "test_naive_1" + std::string(".txt");
	std::string filePathEffective = "test_effective_1" + std::string(".txt");
	std::ofstream resultsNaive(filePathNaive);
	std::ofstream resultsEffective(filePathEffective);

	for (int i = 1; i <= TEST_SIZE + 1; i += 10)
	{
		obv::Segment *dataSample = obv::Service::randomSegments(i, double(0.001));

		auto start_time = std::chrono::high_resolution_clock::now();

		obv::Service::intersectNaive(dataSample, i);

		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		resultsNaive << i << " " << duration.count() << std::endl;

		start_time = std::chrono::high_resolution_clock::now();

		obv::Service::intersectEffective(dataSample, i);

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

	for (int i = TEST_SIZE; i >= 100; i -= 10)
	{
		obv::Segment *dataSample = obv::Service::randomSegments(TEST_SIZE, double(1 / i));

		auto start_time = std::chrono::high_resolution_clock::now();

		obv::Service::intersectNaive(dataSample, TEST_SIZE);

		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		resultsNaive << i << " " << duration.count() << std::endl;

		start_time = std::chrono::high_resolution_clock::now();

		obv::Service::intersectEffective(dataSample, TEST_SIZE);

		end_time = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		resultsEffective << i << " " << duration.count() << std::endl;
	}

	resultsNaive.close();
	resultsEffective.close();
}
