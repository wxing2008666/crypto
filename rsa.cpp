#include "rsa.h"
#include <ctime>
#include <random>
#include <chrono>

#define DEBUG
#define DEBUG_PRIME
const ull LEFTBOARD = 1000;
const ull RIGHTBOARD = 1000000000;
// const ull RIGHTBOARD = 1000000;

std::string rsa::encode(const std::string& input) {

	#ifdef DEBUG_PRIME
		// generate prime tests
		for (int i = 0; i < 100; ++i) {
			time_t start = time(NULL); 
			ul prime = generate_prime();
			time_t end = time(NULL);
			cout << "Prime : " << prime << "; Time : " << end - start << " sec" << endl;
		}
	#endif

	// Generate all keys
	generate_keys();

	return input;
}

void rsa::generate_keys() {
	cout << "Generate p and q..."
	m_p = generate_prime();
	m_q = generate_prime();

	cout << "p = " << m_p << ", q = " << m_q << endl;
	m_module = module(m_p, m_q);
	cout << "Module: " << m_module << endl;
	m_euler = euler_function(m_p, m_q);
	cout << "Euler function: " << m_euler << endl;
	m_d_key = secret_exponent(m_e_key, m_euler);
	cout << "Secret exponent: " << m_d_key << endl;
	cout << "Public exponent: " << m_e_key << endl;
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

ull rsa::module(ul first_prime, ul second_prime) {
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

ull rsa::secret_exponent(ull e_key, ull euler) {
	ul dkey = euler / e_key;
	while(true) {
		if(((dkey * e_key) % euler ) == 1) 
			break
		else dkey++;
	}
	return dkey;
}
