#include "block_chain.h"
#include "sha256.h"

#include <iostream>
#include <sstream>
#include <chrono>

#include <thread>
#include <future>

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

	vector<future<string>> futures;
		
	auto start = system_clock::now();

	for (size_t i = 0; i < num_threads - 1; i++)
	{
		futures.push_back(async(calculate_hash));
	}

	for (auto &f : futures)
	{
		auto _hash = f.get();
	}

	auto end = system_clock::now();
	duration<double> diff = end - start;

	//cout << "Block mined: " << _hash << " in " << diff.count() << " seconds" << "\n" << endl;
}

//NOT IMPLEMENTED COMPLETELY YET
string block::calculate_hash() noexcept
{
	string str(3, '0');

	while (!found)
	{
		stringstream ss;
		ss << _index << _time << _data << ++(*_nonce) << prev_hash;

		string _current_hash = sha256(ss.str());

		if (_current_hash.substr(0, 3) == str) {
			found = true;
			return _current_hash;
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
