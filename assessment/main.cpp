#include <iostream>
#include <string>
#include "block_chain.h"
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

int const ITERATIONS = 50u; //iterations or nr of blocks
int const DIFFICULTIES_TO_TEST = 5; //testing all difficulties, up to and including

int main()
{
	// Create log file/report
	ofstream data("../my_assessment/data.csv", ofstream::app);

	for (size_t current_difficulty = 1; current_difficulty <= DIFFICULTIES_TO_TEST; current_difficulty++)
	{
		//write the difficulty level to the file
		cout << "orig: " << "diff_" << current_difficulty << ", iterations_" << ITERATIONS;
		data << "orig," << current_difficulty << "," << ITERATIONS;

		// create a block_chain for each difficulty level (1 - 6)
		block_chain bchain;
		//bchain._difficulty = current_difficulty; //setting difficulty for current block_chain
		bchain.set_difficulty(current_difficulty);
		//cout << "bchain.get_difficulty(): " << bchain.get_difficulty() << endl;

		auto start = system_clock::now();
		for (uint32_t i = 0; i < ITERATIONS; ++i)
		{
			cout << "Mining block " << i << "..." << endl;
			bchain.add_block(block(i, string("Block ") + to_string(i) + string(" Data")));
		}
		auto end = system_clock::now();
		duration<double> diff = end - start;
		cout << "time of " << ITERATIONS << " iterations: " << diff.count() << endl;

		//write the time to data
		data << "," << diff.count();

		data << endl;
	}

	// Close the file
	data.close();

    return 0;
}