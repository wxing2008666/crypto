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
	huffman() {
		std::cout << "huffman init " << m_alphabet.size() << std::endl;

	}

	virtual std::string encode(const std::string& input) override;
	virtual std::string decode(const std::string& input) override;

	~huffman() {
		std::cout << "huffman Destruct" << std::endl;
	}
protected:
	void calculate_frequency(const std::string& input);


	std::vector<unit> m_alphabet;
	
};