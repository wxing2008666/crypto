#ifdef __HUFFMAN_H_INCLUDED__
#define __HUFFMAN_H_INCLUDED__

// #include "crypto.h"
#include <iostream>
#include <string>
using namespace std;

class huffman //: public crypto
{
public:
	huffman() {
		std::cout << "huffman init" << std::endl;
	};

	std::string encode(std::string input);
	std::string decode(std::string input);

	~huffman() {

	};
};

#endif