#include "rsa.h"
#include <ctime>
#include <random>
#include <chrono>
#include <string>
#include <algorithm>

#define MSG_BLOCK_SIZE 7

#define DEBUG

std::string rsa::encode(const std::string& input) {
	std::string encoded_msg;
	for (size_t i = 0; i < input.size(); ++i) {

		char current = input.at(i);
		BigInteger block((int) current);
		BigInteger encoded_result = crypt(block, m_e_key, m_module);
		std::string encoded = (string) encoded_result;

		if(encoded.size() != (size_t) MSG_BLOCK_SIZE ) {
			// get count of zeros
			int zeros_count = MSG_BLOCK_SIZE - (int) encoded.size(); 
			std::reverse(encoded.begin(), encoded.end());
			for (int i = 0; i < zeros_count; ++i) {
				encoded += "0";
			}
			std::reverse(encoded.begin(), encoded.end());
		}
		encoded_msg += encoded;
		cout << "[DEBUG] encoded block [" << current << ", " << (int) current << "] is [" << encoded << "]" << endl;
	}
	return encoded_msg;
}

std::string rsa::decode(const std::string& input) {
	std::string decoded_msg;
	int cycles = input.size() / MSG_BLOCK_SIZE;
	for (int i = 0; i < cycles; ++i) {
		std::string buffer;
		for (int j = 0; j < MSG_BLOCK_SIZE; ++j) {
			buffer += input.at(i * MSG_BLOCK_SIZE + j);
		}
		BigInteger block(buffer);
		BigInteger decoded = crypt(block, m_d_key, m_module);
		char symbol = (char) std::stoi(decoded.getNumber());
		cout << "[DEBUG] decoded block [" << buffer << "] is [" << decoded << ", " << symbol << "]"<< endl;
		decoded_msg += symbol;
	}
	return decoded_msg;
}

BigInteger rsa::crypt(BigInteger msg, BigInteger key, BigInteger pkey) {
	return  msg.power(key, pkey);
}

void rsa::generate_keys() {
	cout << "====================================" << endl;
	cout << "Generate p and q..." << endl;
	m_p = 3557; // generate_prime();
	m_q = 2579; // generate_prime();
	m_e_key = 17;//
	cout << "p = "<< m_p << "[" << m_p.getNumber().size() << "], q = " << m_q << "[" << m_q.getNumber().size() << "]" <<  endl;
	m_module = module(m_p, m_q);
	cout << "Module: " << m_module << endl;
	m_euler = euler_function(m_p, m_q);
	cout << "Euler function: " << m_euler << endl;
	BigInteger one(1);
	m_d_key = gcd_extend(m_e_key, m_euler); //m_e_key.power(one, m_euler);
	cout << "Secret exponent: " << m_d_key << endl;
	cout << "Public exponent: " << m_e_key << endl;
	cout << "====================================" << endl;
}

BigInteger rsa::euler_function(BigInteger first_prime, BigInteger second_prime) {
	return (first_prime - 1) * (second_prime - 1);
}

BigInteger rsa::module(BigInteger first_prime, BigInteger second_prime) {
	return first_prime * second_prime;
}

BigInteger rsa::generate_prime() {
	BigInteger prime = 2;
	while(true) {
		prime = prime.random(64);
		if(prime.is_prime()) break;
	}
	return prime;
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