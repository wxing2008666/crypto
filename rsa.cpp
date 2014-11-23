#include "rsa.h"

std::string rsa::encode(const std::string& input) {
	// test is_prime
	for (int i = 0; i < 100; ++i) {
		cout << "Digit " << i << " : is_prime = " << is_prime(i) << endl;
	}
	return input;
}

std::string rsa::decode(const std::string& input) {
	return input;
}

bool rsa::is_prime(int digit) {
	int current_divisor = 2;
	// check if digit has divisors
	while(current_divisor < digit) {
	    if((digit % current_divisor++) == 0) break;
	}
	return current_divisor == digit;
}