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

	// Test bigint 
	BigInteger A("123123123123123123123123123123123123123123123123123123123123123123123123");
	BigInteger B("10");
	BigInteger C = A + B;
	cout << "C = " << C.power(10) << endl; 
	cout << "B ^ 10 " << B.power(10) << endl;


	BigInteger converted_str = input;
	BigInteger encoded = crypt(converted_str, m_e_key, m_module);
	return (string) encoded;
}

std::string rsa::decode(const std::string& input) {
	BigInteger converted_str = input;
	BigInteger decoded = crypt(converted_str, m_d_key, m_module);
	return (string) decoded;
}

BigInteger rsa::crypt(BigInteger msg, BigInteger key, BigInteger pkey) {
	// idea:
	// 2^16 mod n = (((2 ^ 2 mod n)^2 mod n)^2 mod n)^2 mod n

	ul converted_message = 0;
	// while (key) {
	// 	if (key & 1)
	// 		converted_message = (converted_message * msg) % pkey;
	// 	key >>= 1; //divide by 2
	// 	msg = (msg * msg) % pkey;
	// 	cout << "Key: " << key << " Msg: " << msg << " CM: " << converted_message <<endl;
	// }
	return converted_message;
}

void rsa::generate_keys() {
	cout << "====================================" << endl;
	cout << "Generate p and q..." << endl;
	// m_p = generate_prime();
	// m_q = generate_prime();
	// cout << "p = " << m_p << ", q = " << m_q << endl;
	// m_module = module(m_p, m_q);
	// cout << "Module: " << m_module << endl;
	// m_euler = euler_function(m_p, m_q);
	// cout << "Euler function: " << m_euler << endl;
	// m_d_key = gcd_extend(m_e_key, m_euler);
	// cout << "Secret exponent: " << m_d_key << endl;
	// cout << "Public exponent: " << m_e_key << endl;
	// cout << "====================================" << endl;

}


bool rsa::is_prime(BigInteger digit) {
	BigInteger current_divisor = 2;
	// check if digit has divisors
	// while(current_divisor < digit) {
	//     if(!(digit % current_divisor++)) break;
	// }
	return current_divisor == digit;
}

// Extended Euclid algorithm
BigInteger rsa::gcd_extend(BigInteger first_digit, BigInteger second_digit) {
	BigInteger b0 = second_digit, t, q;
	BigInteger x0 = 0, x1 = 1;
	if (second_digit == 1) return 1;
	while (first_digit > 1) {
		q = first_digit / second_digit;
		t = second_digit, second_digit = first_digit % second_digit, first_digit = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

BigInteger rsa::euler_function(BigInteger first_prime, BigInteger second_prime) {
	return (first_prime - 1) * (second_prime - 1);
}

BigInteger rsa::module(BigInteger first_prime, BigInteger second_prime) {
	return first_prime * second_prime;
}

BigInteger rsa::generate_prime() {
	BigInteger prime = 2;
	BigInteger leftBoard = prime.power(100);
	BigInteger rightBoard = prime.power(200);

	while(true) {
	    prime = get_random_number(leftBoard, rightBoard);
	    if(prime.is_prime()) break;
	}
	return prime;
}

BigInteger rsa::get_random_number(BigInteger leftBoard, BigInteger rightBoard) {

	std::random_device random_device;
    std::mt19937 generator(random_device());
	std::uniform_int_distribution<ull> distribution(0, std::numeric_limits<ull>::max());
	BigInteger part = (rightBoard - leftBoard) / std::numeric_limits<ull>::max();
	BigInteger newL = leftBoard + part * distribution(generator);
	BigInteger newR = newL + part;
	return get_random_number(newL , newR);
}
