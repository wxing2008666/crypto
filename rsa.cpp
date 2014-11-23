#include "rsa.h"
#include <ctime>
#include <random>
#include <chrono>

// #define DEBUG
const int LEFTBOARD = 1000;
const int RIGHTBOARD = 1000000;

std::string rsa::encode(const std::string& input) {
	// test is_prime

	#ifdef DEBUG
		for (ul i = 0; i < 100; ++i) {
			cout << "Digit " << i << " : is_prime = " << is_prime(i) << endl;
		}

		// generate prime tests
		for (int i = 0; i < 100; ++i) {
			time_t start = time(NULL); 
			ul prime = generate_prime();
			time_t end = time(NULL);
			cout << "Prime : " << prime << "; Time(s) : " << end - start << endl;
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

// Recursive Euclid algorithm
ul rsa::gcd(ul first_digit, ul second_digit) {
	return (second_digit != 0) ? gcd(second_digit, first_digit % second_digit) : first_digit;
}

ull rsa::euler_function(ul first_prime, ul second_prime) {
	return (first_prime - 1) * (second_prime - 1);
}

ull rsa::modulo(ul first_prime, ul second_prime) {
	return first_prime * second_prime;
}

ul rsa::generate_prime() {
	ul prime = 2;
	while(true) {
	    prime = get_random_number();
	    if(is_prime(prime)) break;
	}
	return prime;
}

ul rsa::get_random_number() {
	std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<ul> distribution(LEFTBOARD, RIGHTBOARD);

    return distribution(generator);
}
