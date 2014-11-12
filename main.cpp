#define HUFFMAN
// #define DES

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
			std::cout << "H = " << h.get_H() << endl;
			std::cout << "C = " << h.get_C() << endl;
			std::cout << "R = " << h.get_C() - h.get_H() << endl;
		#endif

		#ifdef DES
			std::string key;
			cout << "Enter key(8-byte) :";
			cin >> key;
			des d;
			if(key.size() > 8) {
				d.convert_key(key);
				std::string encoded = d.encode(input);
				std::cout << "Encoded string : "<< encoded << std::endl;
				std::cout << "Decoded string : "<< d.decode(encoded) << std::endl;
			} else {
				cout << "Please use 64-bit key!"<< endl;
			}
		#endif
	}
	return 0;
}
