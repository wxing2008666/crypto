#include <iostream>
#include <string>
#include "crypto.h"

using namespace std;

class huffman : public crypto
{
public:
	huffman() {
		std::cout << "huffman init" << std::endl;
	};

	virtual std::string encode(std::string input) override;
	// virtual std::string decode(std::string input) override;

	~huffman() {
		std::cout << "huffman Destruct" << std::endl;
	}
};