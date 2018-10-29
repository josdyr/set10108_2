#include "block_chain.h"
#include "sha256.h"

#include <iostream>
#include <sstream>
#include <chrono>

#include <thread>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// Number of threads to run
//constexpr int THREADS = 10;

// Note that _time would normally be set to the time of the block's creation.
// This is part of the audit a block chain.  To enable consistent results
// from parallelisation we will just use the index value, so time increments
// by one each time: 1, 2, 3, etc.
block::block(uint32_t index, const string &data)
: _index(index), _data(data), _nonce(std::make_shared<std::atomic<uint64_t>>(0)), _time(static_cast<long>(index))
{
}

void block::mine_block(uint32_t difficulty) noexcept
{
	auto num_threads = thread::hardware_concurrency();

	vector<thread> threads;

	auto start = system_clock::now();

#pragma omp parallel num_threads(num_threads)
	calculate_hash(difficulty);

	auto end = system_clock::now();
	duration<double> diff = end - start;

	//cout << "Block mined: " << _hash << " in " << diff.count() << " seconds" << "\n" << endl;
}

void block::calculate_hash(uint32_t difficulty) noexcept
{
	string str(difficulty, '0');

	while (!found)
	{
		stringstream ss;
		ss << _index << _time << _data << ++(*_nonce) << prev_hash;

		string _current_hash = sha256(ss.str());

		if (_current_hash.substr(0, difficulty) == str) {
			found = true;
			_hash = _current_hash;
			
			// Get the thread number
			auto thread_num = omp_get_thread_num();
			// Get the number of threads in operation
			auto total_threads = omp_get_num_threads();
			// Display a message
			//cout << "thread (" << (thread_num + 1) << "/" << total_threads << ") found a signed hash: " << _current_hash << " (_nonce = " << *_nonce << ")" << endl;
		}
	}
}

block_chain::block_chain()
{
    _chain.emplace_back(block(0, "Genesis Block"));
    _difficulty = 3;
}

void block_chain::add_block(block &&new_block) noexcept
{
    new_block.prev_hash = get_last_block().get_hash();
    new_block.mine_block(_difficulty);
    _chain.push_back(new_block);
}
