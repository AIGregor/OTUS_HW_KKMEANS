#include "..\include\tools.h"
#include <fstream>

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
void kkmeans_tools::GenerateData(std::vector<sample_type>& samples)
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
}

/// Generate data for task - starry sky
void kkmeans_tools::GenerateData(int maxVal, int minVal, 
	int count, 
	std::vector<sample_type >& matrix)
{

}
