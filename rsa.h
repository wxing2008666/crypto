#include <iostream>
#include <string>
#include "crypto.h"
#include <vector>
#include "BigInteger.h"
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
	BigInteger m_p; // 32-bit prime digit p
	BigInteger m_q; // 32-bit prime digit q
	BigInteger m_module; // module
	BigInteger m_euler; // Euler function result
	BigInteger m_e_key; // public exponent
	BigInteger m_d_key; // secret exponent

	/* Methods */
	bool is_prime(BigInteger digit);
	BigInteger generate_prime();
	BigInteger gcd_extend(BigInteger first_digit, BigInteger second_digit); 
	BigInteger euler_function(BigInteger first_prime, BigInteger second_prime);
	BigInteger module(BigInteger first_prime, BigInteger second_prime);
	BigInteger get_random_number(BigInteger leftBoard, BigInteger rightBoard);

	BigInteger crypt(BigInteger msg, BigInteger key, BigInteger pkey);

};