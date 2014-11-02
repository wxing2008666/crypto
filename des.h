#include <iostream>
#include <bitset>
#include <vector>
#include "crypto.h"
#include "tables.h"

using namespace std;
using namespace permutations;

const int BLOCK_SIZE_64 = 64;
const int BITS_IN_BYTE = 8;


class des : public crypto
{
public:
	des() {}
	~des() {}

	virtual std::string encode(const std::string& input) override;
	virtual std::string decode(const std::string& input) override;
	/* Change key to bit representation */
	void convert_key(const std::string& input);
protected:
	/* Prepare input string */
	void split_input_string(const std::string& input);
	std::string to_bit_string(const bitset<BLOCK_SIZE_64>& block);
	std::string to_std_string(const bitset<BLOCK_SIZE_64>& block);
	bitset<BLOCK_SIZE_64> initial_permutation(const bitset<BLOCK_SIZE_64>& block);
	std::string calculating(const std::string& input, bool is_encode);

	std::vector<std::bitset<BLOCK_SIZE_64>> blocks;
	bitset<BLOCK_SIZE_64> key;
};