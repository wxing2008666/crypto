#include <iostream>
#include <string>
#include "crypto.h"
#include <bitset>
using namespace std;

const int BLOCK_SIZE_256 = 256;
const int KEY_SIZE = BLOCK_SIZE_256 / 8;
const int BLOCK_SIZE_64 = 64;

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

	void split_input_string(const std::string& input);
};