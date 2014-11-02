#include <iostream>
#include "huffman.h"

int main() {
	std::string input;
	cout << "Enter string to encode :";
	cin >> input;
	if(!input.empty()) {
		huffman h;
		std::string encoded = h.encode(input);
		std::cout << "Encoded string : "<< encoded << std::endl;
		if(!encoded.empty()) {
			std::cout << "Decoded string : "<< h.decode(encoded) << std::endl;
		}
	}
	return 0;
}
