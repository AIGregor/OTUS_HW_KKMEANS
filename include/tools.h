#pragma once

#include <dlib/clustering.h>
#include <dlib/rand.h>

namespace kkmeans_tools
{
	using namespace std;
	using namespace dlib;

	typedef matrix<double, 2, 1> sample_type;

	void FillDataFromInputStream(std::vector<sample_type>& matrix);
	void GenerateData(std::vector<sample_type>& samples);
	void GenerateData(int maxVal, int minVal, int count, std::vector<sample_type>& matrix);
}