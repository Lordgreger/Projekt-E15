#pragma once
#include <string>
#include <iostream>
#include <bitset>
#include <vector>


class CRC
{
public:
	CRC();
	~CRC();

	std::string runCRC(std::string message);
};