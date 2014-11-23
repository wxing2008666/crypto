#include <iostream>
#include <string>
#include "crypto.h"
using namespace std;

typedef unsigned long ul;
typedef unsigned long long ull;


class rsa : public crypto
{
public:
	rsa() {};
	~rsa() {};

	virtual std::string encode(const std::string& input) override;
	virtual std::string decode(const std::string& input) override;

private:
	/* Variables */
	ul m_p; // 32-bit prime digit p
	ul m_q; // 32-bit prime digit q




	/* Methods */
	bool is_prime(ul digit);
	ul gcd(ul first_digit, ul second_digit); 
	ull euler_function(ul first_prime, ul second_prime);

};