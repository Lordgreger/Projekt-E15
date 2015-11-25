#pragma once
#include <string>
#include <bitset>

class CharDefinition
{
public:
	CharDefinition();
	~CharDefinition();

	std::string charToBinary(std::string chars);
	std::string binaryToChar(std::string bins);

protected:
	std::string intToString(int bit);

	std::string charsDefined;

};

