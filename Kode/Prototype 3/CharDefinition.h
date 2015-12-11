#pragma once
#include "DLL.h"
#include <string>
#include <bitset>
#include "Transportlag.h"

class CharDefinition
{
public:
	CharDefinition();
	~CharDefinition();

	void applyCharDef(std::string input);
	std::string recieverCharDef();

protected:
	std::string charToBinary(std::string chars);
	std::string binaryToChar(std::string bins);

	std::string intToString(int bit);
	std::string charsDefined;
	Transportlag transP;

};

