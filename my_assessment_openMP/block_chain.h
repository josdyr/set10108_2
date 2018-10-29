#pragma once

#include <string>
#include <vector>
#include <atomic>

class block
{
private:
    // The index of the block in the chain.
    uint32_t _index;
    // A modifier used to get a suitable block.
    //uint64_t _nonce;
	std::shared_ptr<std::atomic<uint64_t>> _nonce;
    // Data stored in the block.
    std::string _data;
    // Hash code of this block.
    std::string _hash;
    // Time code block was created.
    long _time;

	bool found = false;

    void calculate_hash(uint32_t difficulty) noexcept;

public:
    block(uint32_t index, const std::string &data);

    // Difficulty is the minimum number of zeros we require at the
    // start of the hash.
    void mine_block(uint32_t difficulty) noexcept;

    inline const std::string& get_hash() const noexcept { return _hash; }

    // Hash code of the previous block in the chain.
    std::string prev_hash;
};

class block_chain
{
private:
    uint32_t _difficulty;

    std::vector<block> _chain;

    inline const block& get_last_block() const noexcept { return _chain.back(); }

public:
	//getters and setters for _difficulty
	void set_difficulty(uint32_t d) {
		_difficulty = d;
	}

	uint32_t get_difficulty() {
		return _difficulty;
	}

    block_chain();

    void add_block(block &&new_block) noexcept;
};