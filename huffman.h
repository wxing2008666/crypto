#include <iostream>
#include <string>
#include "crypto.h"

using namespace std;

struct symbol{
	char symbol;
	double frequency;
	string bytecode;
};

class huffman : public crypto
{
public:
	huffman() {
		std::cout << "huffman init" << std::endl;
	};

	virtual std::string encode(const std::string& input) override;
	virtual std::string decode(const std::string& input) override;

	~huffman() {
		std::cout << "huffman Destruct" << std::endl;
	}
protected:
	void 
};