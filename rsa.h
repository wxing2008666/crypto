#include <iostream>
#include <string>
#include "crypto.h"
using namespace std;

class rsa : public crypto
{
public:
	rsa() {};
	~rsa() {};

	virtual std::string encode(const std::string& input) override;
	virtual std::string decode(const std::string& input) override;

private:
	bool is_prime(int digit);
};