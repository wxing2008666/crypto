// #define HUFFMAN
#define DES

#include <iostream>

#ifdef HUFFMAN
	#include "huffman.h"
#endif

#ifdef DES
	#include "des.h"
#endif

using namespace std;

int main() {
	std::string input;
	cout << "Enter string to encode :";
	cin >> input;
	if(!input.empty()) {
		#ifdef HUFFMAN
			huffman h;
			std::string encoded = h.encode(input);
			std::cout << "Encoded string : "<< encoded << std::endl;
			if(!encoded.empty()) {
				std::cout << "Decoded string : "<< h.decode(encoded) << std::endl;
			}
		#endif

		#ifdef DES
			des d;
		#endif
	}
	return 0;
}
