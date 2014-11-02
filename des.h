#include <iostream>
#include "crypto.h"
#include "tables.h"

using namespace std;
using namespace permutations;


class des : public crypto
{
public:
	des() {}
	~des() {}

	virtual std::string encode(const std::string& input) override;
	virtual std::string decode(const std::string& input) override;
protected:
	void split_input_string(const std::string& input);


	
};