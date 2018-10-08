#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <chrono>
#include <thread>
#include <fstream>
#include <mutex>
#include <atomic>

using namespace std;
using namespace std::chrono;

mutex mut;
int avg_count = 0;
atomic<double> pi;

void monte_carlo_pi(size_t iterations, shared_ptr<atomic<double>> pi)
{
	// Seed with real random number if available
	random_device r;
	// Create random number generator
	default_random_engine e(r());
	// Create a distribution - we want doubles between 0.0 and 1.0
	uniform_real_distribution<double> distribution(0.0, 1.0);

	// Keep track of number of points in circle
	unsigned int in_circle = 0;
	// Iterate
	for (size_t i = 0; i < iterations; ++i)
	{
		// Generate random point
		auto x = distribution(e);
		auto y = distribution(e);
		// Get length of vector defined - use Pythagarous
		auto length = sqrt((x * x) + (y * y));
		// Check if in circle
		if (length <= 1.0)
			++in_circle;
	}

	// Calculate pi
	if (avg_count == 0)
	{
		/*mut.lock();*/
		*pi = ((4.0 * in_circle) / static_cast<double>(iterations));
		/*mut.unlock();*/
	}
	else {
		/*mut.lock();*/
		*pi = (*pi + ((4.0 * in_circle) / static_cast<double>(iterations))) / 2;
		/*mut.unlock();*/
	}
	avg_count++;

	double accuracy = *pi / (3.14159265359);
	if (accuracy > 1)
	{
		std::cout << "pi avg: " << *pi << "\t" << "accuracy: " << 1 - (accuracy - 1) << "\n";
	}
	else {
		std::cout << "pi avg: " << *pi << "\t" << "accuracy: " << accuracy << "\n";
	}
}

int main(int argc, char **argv)
{
	// Create a shared int value
	//auto pi = make_shared<double>(0);

	// Create a shared int value
	auto pi = make_shared<atomic<double>>();

	// Create data file
	ofstream data("montecarlo_pi_value.csv", ofstream::out);

	for (size_t i = 0; i <= 6; ++i)
	{
		auto total_threads = static_cast<unsigned int>(pow(2.0, i));
		total_threads = thread::hardware_concurrency();
		// Write number of threads
		cout << "Number of threads = " << total_threads << endl;
		// Write number of threads to the file
		data << "num_of_threads_" << total_threads;
		// Now execute 100 iterations
		for (size_t iters = 0; iters < 10; ++iters)
		{
			// Get the start time
			auto start = system_clock::now();
			// We need to create total_threads threads
			vector<thread> threads;
			for (size_t n = 0; n < total_threads; ++n)
				// Working in base 2 to make things a bit easier
				threads.push_back(thread(monte_carlo_pi, static_cast<unsigned int>(pow(2.0, 24.0 - i)), pi));
			// Join the threads (wait for them to finish)
			for (auto &t : threads)
				t.join();
			// Get the end time
			auto end = system_clock::now();
			// Get the total time
			auto total = end - start;
			// Convert to milliseconds and output to file
			data << ", " << duration_cast<milliseconds>(total).count();
			std::cout << "duration_cast: " << duration_cast<milliseconds>(total).count() << "ms" << "\n";
			// std::cout << "pi: " << *pi << "\n";
		}
		data << endl;
	}
	// Close the file
	data.close();
	return 0;
}