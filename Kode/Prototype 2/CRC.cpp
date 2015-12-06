#include "CRC.h"


CRC::CRC()
{
	charsDefined = "0123456789abcdefghijklmnopqrstuvwxyzæøåABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅ !#¤%&/()=+?,;.:-_'*<>\"";
}

CRC::~CRC()
{
}

std::string CRC::runCRC(std::string aString)
{
	std::string tempString = aString;
	const char *tempChar = tempString.c_str();

	crc = 0;
	buf = tempChar;
	len = strlen(buf);
	rc_crc32();
	convertCRC();
	return returnSum;
}

void CRC::rc_crc32()
{
	static uint32_t table[256];
	static int have_table = 0;
	uint32_t rem;
	uint8_t octet;
	int i, j;
	const char *p, *q;

	/* This check is not thread safe; there is no mutex. */
	if (have_table == 0) {
		/* Calculate CRC table. */
		for (i = 0; i < 256; i++) {
			rem = i;  /* remainder from polynomial division */
			for (j = 0; j < 8; j++) {
				if (rem & 1) {
					rem >>= 1;
					rem ^= 0xedb88320;
				}
				else
					rem >>= 1;
			}
			table[i] = rem;
		}
		have_table = 1;
	}

	crc = ~crc;
	q = buf + len;
	for (p = buf; p < q; p++) {
		octet = *p;  /* Cast to unsigned octet. */
		crc = (crc >> 8) ^ table[(crc & 0xff) ^ octet];
	}
	checksum = ~crc;
}

void CRC::convertCRC()
{
	std::stringstream ss;
	ss << std::hex << checksum;
	std::string tempString;
	ss >> tempString;

	returnSum = hexToString(tempString);
}

std::string CRC::hexToString(std::string hex)
{
	std::string output = "";
	for (size_t i = 0; i <= hex.size(); i++)
	{
		for (size_t k = 0; k < charsDefined.size(); k++)
		{
			if (hex[i] == charsDefined[k])
			{
				output += intToStringHex(k);
			}
		}
	}
	return output;
}

std::string CRC::intToStringHex(int bit)
{
	std::string binary = "";
	for (int i = 1; i <= 4; i++)
	{
		if (std::bitset<4>(bit)[4 - i] == 1)
		{
			binary += "1";
		}
		else
		{
			binary += "0";
		}
	}
	//binary += " ";

	return binary;
}