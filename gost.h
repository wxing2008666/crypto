#include <iostream>
#include <string>
#include "crypto.h"

using namespace std;

class gost : public crypto
{
public:
	gost() {};
	~gost() {};

	virtual std::string encode(const std::string& input) override;
	virtual std::string decode(const std::string& input) override;
};