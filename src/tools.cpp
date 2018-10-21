#include "..\include\tools.h"
#include <fstream>
#include <random>

/// Fill data from input stream
void kkmeans_tools::FillDataFromInputStream(std::vector<sample_type>& samples)
{
	sample_type m;

	while (cin)
	{
		string line;
		char delim = ';';
		getline(cin, line);
		std::istringstream iss(line);
		
		int i = 0;
		while ( getline(iss, line, delim)  && i < 2)
		{	
			double x = atof(line.c_str());
			if (x != 0)
				m(i++) = x;
		}
		samples.push_back(m);
	}
}

/// Generate data like in sample
void kkmeans_tools::GenerateData(std::vector<sample_type>& samples, bool save)
{
	sample_type m;

	dlib::rand rnd;

	// we will make 50 points from each class
	const long num = 50;

	// make some samples near the origin
	double radius = 0.5;
	for (long i = 0; i < num; ++i)
	{
		double sign = 1;
		if (rnd.get_random_double() < 0.5)
			sign = -1;
		m(0) = 2 * radius*rnd.get_random_double() - radius;
		m(1) = sign*sqrt(radius*radius - m(0)*m(0));

		// add this sample to our set of samples we will run k-means 
		samples.push_back(m);
	}

	// make some samples in a circle around the origin but far away
	radius = 10.0;
	for (long i = 0; i < num; ++i)
	{
		double sign = 1;
		if (rnd.get_random_double() < 0.5)
			sign = -1;
		m(0) = 2 * radius*rnd.get_random_double() - radius;
		m(1) = sign*sqrt(radius*radius - m(0)*m(0));

		// translate this point away from the origin
		m(0) += 10;
		m(1) += 10;

		// add this sample to our set of samples we will run k-means 
		samples.push_back(m);
	}

	// make some samples in a circle around the point (25,25) 
	radius = 4.0;
	for (long i = 0; i < num; ++i)
	{
		double sign = 1;
		if (rnd.get_random_double() < 0.5)
			sign = -1;
		m(0) = 2 * radius*rnd.get_random_double() - radius;
		m(1) = sign*sqrt(radius*radius - m(0)*m(0));

		// translate this point away from the origin
		m(0) += 25;
		m(1) += 25;

		// add this sample to our set of samples we will run k-means 
		samples.push_back(m);
	}

	if (save)
		Save_to_file(samples, "Sample_data.csv");
}

/// Generate data for task - starry sky
void kkmeans_tools::GenerateStarrySky(int minVal, int maxVal,
	int count, 
	std::vector<sample_type>& matrix,
	bool save)
{
	std::uniform_int_distribution<int> range(minVal, maxVal);
	std::random_device rd;

	sample_type m;

	for (int i = 0; i < count; ++i)
	{
		m(0) = range(rd);
		m(1) = range(rd);

		matrix.push_back(m);
	}

	if (save)
		Save_to_file(matrix, "Starry_sky.csv");
}

void kkmeans_tools::Save_to_file(std::vector<sample_type>& matrix, std::string fileName)
{
	std::ofstream out;

	out.open(fileName);
	if (out.is_open())
	{

		for (unsigned long i = 0; i < matrix.size(); ++i)
		{
			out << matrix[i](0) << ";";
			out << matrix[i](1) << "\n";
		}
	}
}