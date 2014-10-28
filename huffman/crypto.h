#ifdef __CRYPTO_H_INCLUDED__
#define __CRYPTO_H_INCLUDED__

#include <string>

class crypto
{
public:
	virtual std::string encode(std::string input) = 0;
	virtual std::string decode(std::string input) = 0;
};

#endif