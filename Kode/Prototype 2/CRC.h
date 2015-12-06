#pragma once
#include <inttypes.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <bitset>


class CRC
{
public:
	CRC();													//Constructor skal kaldes med charsDefined
	~CRC();

	std::string runCRC(std::string aString);				//Laver og returnerer CRC bitstreng på et stringudtryk

protected:
	void rc_crc32();										//Laver tabel og konverterer chars til et CRC check
	void convertCRC();										//Konverterer CRC fra hex til bitstreng
	std::string hexToString(std::string hex);				
	std::string intToStringHex(int bit);

	uint32_t crc;											//attribut benyttet i rc_crc32
	const char * buf;										//attribut benyttet i rc_crc32
	size_t len;												//attribut benyttet i rc_crc32
	uint32_t checksum;										//Indeholder CRC i form af hex
	std::string returnSum;									//Indeholder CRC bitstreng
	std::string binary;
	std::string charsDefined;
};