// #define HUFFMAN
// #define DES
// #define GOST
#define RSA

#include <iostream>

#ifdef HUFFMAN
	#include "huffman.h"
#endif

#ifdef DES
	#include "des.h"
#endif

#ifdef GOST
	#include "gost.h"
#endif

#ifdef RSA
	#include "rsa.h"
#endif

using namespace std;

int main() {
	std::string input;
	cout << "Enter string to encode :";
	getline(cin, input);
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

		#ifdef GOST
			std::string key;
			cout << "Enter key(256 bits) :";
			cin >> key;
			gost g;
			g.set_key(key);
			std::string encoded = g.encode(input);
			std::cout << "Encoded string : "<< encoded << std::endl;
			std::cout << "Decoded string : "<< g.decode(encoded) << std::endl;
		#endif

		#ifdef RSA
			rsa r;
			r.generate_keys();
			std::string encoded = r.encode(input);
			std::cout << "Encoded string : "<< encoded << std::endl;
			std::cout << "Decoded string : "<< r.decode(encoded) << std::endl;
		#endif
	}
	return 0;
}
