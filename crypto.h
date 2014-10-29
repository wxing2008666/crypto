#include <string>

class crypto
{
public:
	virtual std::string encode(const std::string& input) = 0;
	virtual std::string decode(const std::string& input) = 0;
};