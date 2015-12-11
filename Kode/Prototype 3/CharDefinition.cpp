#include "CharDefinition.h"


CharDefinition::CharDefinition()
{
	charsDefined = "0123456789abcdefghijklmnopqrstuvwxyzæøåABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅ !#¤%&/()=+?,;.:-_'*<>\"";
}

CharDefinition::~CharDefinition()
{

}

void CharDefinition::applyCharDef(std::string input)
{
	input = charToBinary(input);
	transP.senderTransport(input);
}

std::string CharDefinition::recieverCharDef()
{
	return binaryToChar(transP.receiverTransport());
}


std::string CharDefinition::charToBinary(std::string chars)
{
	std::string output = "";
	for (int i = 0; i <= chars.size(); i++)
	{
		for (int k = 0; k < charsDefined.size(); k++)
		{
			if (chars[i] == charsDefined[k])
			{
				output += intToString(k);
			}
		}
	}
	return output;
}

std::string CharDefinition::binaryToChar(std::string bins)
{
	std::string output = "";

	for (int i = 1; i * 8 - 1 < bins.size(); i++)
	{
		int binary = 0;

		if (bins[i * 8-1] == char('1'))
		{
			binary += 1;
		}
		if (bins[i * 8 -2] == char('1'))
		{
			binary += 2;
		}
		if (bins[i * 8 -3] == char('1'))
		{
			binary += 4;
		}
		if (bins[i * 8 -4] == char('1'))
		{
			binary += 8;
		}
		if (bins[i * 8 -5] == char('1'))
		{
			binary += 16;
		}
		if (bins[i * 8 -6] == char('1'))
		{
			binary += 32;
		}
		if (bins[i * 8 -7] == char('1'))
		{
			binary += 64;
		}
		if (bins[i * 8 -8] == char('1'))
		{
			binary += 128;
		}
		output += charsDefined[binary];
	}
	return output;
}

std::string CharDefinition::intToString(int bit)
{
	std::string binary = "";
	for (int i = 1; i<=8 ; i++)
	{
		if (std::bitset<8>(bit)[8-i] == 1)
		{
			binary += "1";
		}
		else
		{
			binary += "0";
		}
	}

	return binary;
}