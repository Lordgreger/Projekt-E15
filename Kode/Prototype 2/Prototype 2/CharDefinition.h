#pragma once
#include "DLL.h"
#include <string>
#include <bitset>

class CharDefinition
{
public:
	CharDefinition();
	~CharDefinition();

	void applyCharDef(std::string input);

protected:
	std::string charToBinary(std::string chars);
	std::string binaryToChar(std::string bins);

	std::string intToString(int bit);
	std::string charsDefined;
	DLL dll;

};

