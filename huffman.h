#include <iostream>
#include <string>
#include "crypto.h"
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>

using namespace std;

struct unit{
	char symbol;
	double frequency;
	string bytecode;
};

class huffman : public crypto
{
public:
	huffman() {}
	~huffman() {}

	virtual std::string encode(const std::string& input) override;
	virtual std::string decode(const std::string& input) override;

protected:
	void calculate_frequency(const std::string& input);
	void change_bytecode(std::vector<unit>& v, char byte);
	void current_tree_state(const std::vector<std::vector<unit>>& tree);

	std::vector<unit> m_alphabet;
	std::vector<unit> codes;
};