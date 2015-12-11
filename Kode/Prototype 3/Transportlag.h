#pragma once
#include "DLL.h"
#include <vector>
#include <string>
#include <bitset>
#include <iostream>


class Transportlag
{
public:
	Transportlag();
	~Transportlag();

	std::string senderTransport(std::string enTekst);
	std::string receiverTransport();
	int binaryToDecimal(std::string bins);
	

private:
	
	std::string intToString(int talTilKonvertering);

	std::vector<std::string> senderBuffer;
	std::vector<std::string> receiverBuffer;
	void sendSegment(std::string etSegment);
	std::string waitForMessage();
	int numberOfSequences;
	DLL dll;

};
