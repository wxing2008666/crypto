#include "rsa.h"
#include <ctime>
#include <random>
#include <chrono>
#include <string>

#define DEBUG
// #define DEBUG_PRIME

/* Constants */
const ull LEFTBOARD = 10000;
const ull RIGHTBOARD = 100000;
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

	ull converted_str = std::stoull(input);
	ull encoded = crypt(converted_str, m_e_key, m_module);
	return std::to_string(encoded);
}

std::string rsa::decode(const std::string& input) {
	ull converted_str = std::stoull(input);
	ull decoded = crypt(converted_str, m_d_key, m_module);
	return std::to_string(decoded);
}
vector<int> rsa::get_multipliers(ull key) {
	std::vector<int> multipliers;
	ul i = 2;
	 

	while(i <= key) {
		if((key % 2) != 0) {
			multipliers.push_back(1);
			key -= 1;
			continue;
		}
		if((key % i) == 0) {
			multipliers.push_back(i);
			key = key / i;
		} else {
			i = i + 1;		
		}
	}


	return multipliers;
}

ull rsa::crypt(ull msg, ul key, ul pkey) {
	// idea:
	// 2^16 mod n = (((2 ^ 2 mod n)^2 mod n)^2 mod n)^2 mod n

	ul converted_message = 0;
	while (key) {
		if (key & 1)
			converted_message = (converted_message * msg) % pkey;
		key >>= 1; //divide by 2
		msg = (msg * msg) % pkey;
		cout << "Key: " << key << " Msg: " << msg << " CM: " << converted_message <<endl;
	}
	return converted_message;
}

void rsa::generate_keys() {
	cout << "====================================" << endl;
	cout << "Generate p and q..." << endl;
	m_p = generate_prime();
	m_q = generate_prime();
	cout << "p = " << m_p << ", q = " << m_q << endl;
	m_module = module(m_p, m_q);
	cout << "Module: " << m_module << endl;
	m_euler = euler_function(m_p, m_q);
	cout << "Euler function: " << m_euler << endl;
	m_d_key = gcd_extend(m_e_key, m_euler);
	cout << "Secret exponent: " << m_d_key << endl;
	cout << "Public exponent: " << m_e_key << endl;
	cout << "====================================" << endl;

}


bool rsa::is_prime(ul digit) {
	ul current_divisor = 2;
	// check if digit has divisors
	while(current_divisor < digit) {
	    if(!(digit % current_divisor++)) break;
	}
	return current_divisor == digit;
}

// Extended Euclid algorithm
ul rsa::gcd_extend(ul first_digit, ul second_digit) {
	int b0 = second_digit, t, q;
	int x0 = 0, x1 = 1;
	if (second_digit == 1) return 1;
	while (first_digit > 1) {
		q = first_digit / second_digit;
		t = second_digit, second_digit = first_digit % second_digit, first_digit = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
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
