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

	void senderTransport(std::string enTekst);
	std::string receiverTransport();




private:
	std::string intToString(int talTilKonvertering);

	std::vector<std::string> senderBuffer;
	std::vector<std::string> receiverBuffer;
	void sendSegment(std::string etSegment);
	std::string waitForACK();
	int numberOfSequences;
	DLL dll;

};
