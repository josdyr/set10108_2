#include <iostream>
#include <string>
#include "block_chain.h"
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
    block_chain bchain;

	auto start = system_clock::now();
    for (uint32_t i = 1; i < 100u; ++i)
    {
        cout << "Mining block " << i << "..." << endl;
        bchain.add_block(block(i, string("Block ") + to_string(i) + string(" Data")));
    }
	auto end = system_clock::now();
	duration<double> diff = end - start;
	cout << "time of 100 iterations: " << diff.count() << endl;

    return 0;
}