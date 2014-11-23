#include "rsa.h"

#define DEBUG

std::string rsa::encode(const std::string& input) {
	// test is_prime
	#ifdef DEBUG
		for (ul i = 0; i < 100; ++i) {
			cout << "Digit " << i << " : is_prime = " << is_prime(i) << endl;
		}
	#endif
	return input;
}

std::string rsa::decode(const std::string& input) {
	return input;
}

bool rsa::is_prime(ul digit) {
	ul current_divisor = 2;
	// check if digit has divisors
	while(current_divisor < digit) {
	    if((digit % current_divisor++) == 0) break;
	}
	return current_divisor == digit;
}

ul rsa::gdc(ul first_digit, ul second_digit) {
	return (second_digit != 0) ? gcd(second_digit, first_digit % second_digit) : first_digit;
}