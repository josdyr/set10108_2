#include <iostream>
#include <string>
#include "block_chain.h"
#include <chrono>
#include <fstream>
#include "assert.h"

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



	/*ifstream temp_file;
	temp_file.open("temp.txt");
	ifstream sample1;
	sample1.open("sample1.txt");

	string s;
	string t;
	int hash_count = 0;
	while (hash_count <= 100)
	{
		getline(temp_file, s);
		getline(temp_file, t);
		if (s == t)
		{
			cout << "true" << endl;
		}
	}
	temp_file.close();
	sample1.close();*/

    return 0;
}