#pragma once
#include "DLL.h"
#include <vector>
#include <string>
#include <bitset>
#include <iostream>


class Transportlag														//Udviddet Stop-n-wait inspireret af TCP  -----  Kaldes fra CharDef, retunerer en string
{
public:
	Transportlag();
	~Transportlag();

	std::string senderTransport(std::string enTekst);					//Afsender rolle, sender segmenter derefter forventer ACK p� det.
	std::string receiverTransport();									//Modtager rolle, venter p� en forbindelse og sender ACK p� segmenter.

	

private:
	int binaryToDecimal(std::string bins);								
	std::string intToString(int talTilKonvertering);

	std::vector<std::string> senderBuffer;
	std::vector<std::string> receiverBuffer;
	void sendSegment(std::string etSegment);							//Send segment til DLL
	std::string waitForMessage();										//Modtag segment fra DLL
	int numberOfSequences;
	DLL dll;							

};
