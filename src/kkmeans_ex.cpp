// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*
This is an example illustrating the use of the kkmeans object
and spectral_cluster() routine from the dlib C++ Library.

The kkmeans object is an implementation of a kernelized k-means clustering
algorithm.  It is implemented by using the kcentroid object to represent
each center found by the usual k-means clustering algorithm.

So this object allows you to perform non-linear clustering in the same way
a svm classifier finds non-linear decision surfaces.

This example will make points from 3 classes and perform kernelized k-means
clustering on those points.  It will also do the same thing using spectral
clustering.

The classes are as follows:
- points very close to the origin
- points on the circle of radius 10 around the origin
- points that are on a circle of radius 4 but not around the origin at all
*/

#include <iostream>
#include <vector>

#include "tools.h"

int main(int argc, char *argv[])
{
	using namespace kkmeans_tools;

	if (argc < 2)
	{
		cout << "Error: There is no clasters number. Please, input clasters number." << endl;
		return 0;
	}
			
	bool saveData = false;
	bool saveStarry_sky = false;

	// Clusters number
	long clustersNumbers = 0;

	for (int i = 1; i < argc; ++i)
	{
		if (!strcmp(argv[i], "-g"))
		{
			saveData = true;
			continue;
		}		

		if (!strcmp(argv[i], "-s"))
		{
			saveStarry_sky = true;
			continue;
		}	

		clustersNumbers = atol(argv[i]);
	}

	if (clustersNumbers == 0 && !saveStarry_sky && !saveData)
	{
		cout << "Error: Parameter is invalide. Please, input clasters number or other parameters." << endl;
		return 0;
	}

	// Here we declare that our samples will be 2 dimensional column vectors.  
	// (Note that if you don't know the dimensionality of your vectors at compile time
	// you can change the 2 to a 0 and then set the size at runtime)
	typedef matrix<double, 2, 1> sample_type;

	// Now we are making a typedef for the kind of kernel we want to use.  I picked the
	// radial basis kernel because it only has one parameter and generally gives good
	// results without much fiddling.
	typedef radial_basis_kernel<sample_type> kernel_type;


	// Here we declare an instance of the kcentroid object.  It is the object used to 
	// represent each of the centers used for clustering.  The kcentroid has 3 parameters 
	// you need to set.  The first argument to the constructor is the kernel we wish to 
	// use.  The second is a parameter that determines the numerical accuracy with which 
	// the object will perform part of the learning algorithm.  Generally, smaller values 
	// give better results but cause the algorithm to attempt to use more dictionary vectors 
	// (and thus run slower and use more memory).  The third argument, however, is the 
	// maximum number of dictionary vectors a kcentroid is allowed to use.  So you can use
	// it to control the runtime complexity.  
	kcentroid<kernel_type> kc(kernel_type(0.1), 0.01, 8);

	// Now we make an instance of the kkmeans object and tell it to use kcentroid objects
	// that are configured with the parameters from the kc object we defined above.
	kkmeans<kernel_type> test(kc);

	std::vector<sample_type> samples;
	std::vector<sample_type> samples_starry_sky;
	std::vector<sample_type> samples_data;

	std::vector<sample_type> initial_centers;

	// Genarate data like in sample
	if (saveData)
		kkmeans_tools::GenerateData(samples_data, true);

	// Generate data for task - StarrySky
	if (saveStarry_sky)
		kkmeans_tools::GenerateStarrySky(-100, 100, 200, samples_starry_sky, true);
		
	// Read data from file
	
	if (clustersNumbers != 0)
		kkmeans_tools::FillDataFromInputStream(samples);
	else
		return 0;

	// tell the kkmeans object we made that we want to run k-means with k set to 3. 
	test.set_number_of_centers(clustersNumbers);

	// You need to pick some initial centers for the k-means algorithm.  So here
	// we will use the dlib::pick_initial_centers() function which tries to find
	// n points that are far apart (basically).  
	pick_initial_centers(clustersNumbers, initial_centers, samples, test.get_kernel());

	// now run the k-means algorithm on our set of samples.  
	test.train(samples, initial_centers);

	// now loop over all our samples and print out their predicted class.  In this example
	// all points are correctly identified.
	std::ofstream out;
	std::string fileName = "clasters.csv";

	out.open(fileName);
	if (out.is_open())
	{

		for (unsigned long i = 0; i < samples.size(); ++i)
		{
			// to file
			out << samples[i](0) << ";";
			out << samples[i](1) << ";";
			out << test(samples[i]) << "\n";
			
			// to consol
			cout << samples[i](0) << ";";
			cout << samples[i](1) << ";";
			cout << test(samples[i]) << "\n";
		}
	}
}
