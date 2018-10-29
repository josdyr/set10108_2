#include "block_chain.h"
#include "sha256.h"

#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <fstream>
#include <mutex>
#include "assert.h"

using namespace std;
using namespace std::chrono;

// Note that _time would normally be set to the time of the block's creation.
// This is part of the audit a block chain.  To enable consistent results
// from parallelisation we will just use the index value, so time increments
// by one each time: 1, 2, 3, etc.
block::block(uint32_t index, const string &data)
: _index(index), _data(data), _nonce(0), _time(static_cast<long>(index)) {
}

void block::mine_block(uint32_t difficulty) noexcept {

	ofstream data("../my_assessment/sample.csv", ofstream::app);

	auto num_threads = thread::hardware_concurrency();

	vector<thread> threads;
	auto start = system_clock::now();
	for (unsigned int i = 0; i < num_threads; ++i) {
		threads.push_back(thread(&block::calculate_hash, this, difficulty));
	}
	for (auto &t : threads) {
		t.join();
	}
    auto end = system_clock::now();
    duration<double> diff = end - start;

	//data << _hash << "," << diff.count();
	data << _hash << endl;

    cout << "Block mined: " << _hash << " in " << diff.count() << " seconds" << "\n" << endl;
	
}

mutex mut;

void block::calculate_hash(uint32_t difficulty) noexcept {
	string str(difficulty, '0');
	while (!found)
	{
		stringstream ss;
		mut.lock();
		ss << _index << _time << _data << ++_nonce << prev_hash;
		string _current_hash = sha256(ss.str());
		mut.unlock();
		if (_current_hash.substr(0, difficulty) == str) {
			found = true;
			_hash = _current_hash;
			cout << "_nonce: " << _nonce << "\t _current_hash: " << _current_hash << endl;
		}
	}
}

block_chain::block_chain() {
    _chain.emplace_back(block(0, "Genesis Block"));
    //_difficulty = 5; // we want to set the difficulty from the main()
}

void block_chain::add_block(block &&new_block) noexcept {
    new_block.prev_hash = get_last_block().get_hash();
    new_block.mine_block(_difficulty);
    _chain.push_back(new_block);
}
