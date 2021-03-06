#include <iostream>
#include <string>
#include "crypto.h"
#include <bitset>
#include <vector>
using namespace std;

const int BLOCK_SIZE_256 = 256;
const int KEY_SIZE = BLOCK_SIZE_256 / 8;
const int BLOCK_SIZE_64 = 64;
const int BLOCK_SIZE_32 = 32;

class gost : public crypto
{
public:
	gost() {};
	~gost() {};

	virtual std::string encode(const std::string& input) override;
	virtual std::string decode(const std::string& input) override;
	void set_key(const std::string& input);

private:
	bitset<BLOCK_SIZE_256> key;
	vector<bitset<BLOCK_SIZE_64>> blocks;
	bitset<BLOCK_SIZE_32> get_key_i(int i, bool encode);

	std::string encrypt(const std::string& input, bool encode);
	void split_input_string(const std::string& input);
	std::string to_std_string(const bitset<BLOCK_SIZE_64>& block);

};