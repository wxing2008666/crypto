#include <iostream>
#include <string>
#include "crypto.h"
using namespace std;

typedef unsigned long ul;
typedef unsigned long long ull;


class rsa : public crypto
{
public:
	// m_e_key use Fermat number 
	rsa() : m_e_key(65537) 
	{};
	~rsa() {};

	virtual std::string encode(const std::string& input) override;
	virtual std::string decode(const std::string& input) override;
	void generate_keys();

private:
	/* Variables */
	ul m_p; // 32-bit prime digit p
	ul m_q; // 32-bit prime digit q
	ull m_module; // module
	ull m_euler; // Euler function result
	ull m_e_key; // public exponent
	ull m_d_key; // secret exponent

	/* Methods */
	bool is_prime(ul digit);
	ul generate_prime();
	ul gcd_extend(ul first_digit, ul second_digit); 
	ull euler_function(ul first_prime, ul second_prime);
	ull module(ul first_prime, ul second_prime);
	ul get_random_number();

	ull crypt(ull msg, ull key, ull pkey);
};