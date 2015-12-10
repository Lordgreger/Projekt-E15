#include "Transportlag.h"

Transportlag::Transportlag()
{
}

Transportlag::~Transportlag()
{
}

void Transportlag::senderTransport(std::string enTekst)
{
	senderBuffer.clear();
	numberOfSequences = enTekst.size() / 80;

	if (enTekst.size() % 80 != 0)
	{
		numberOfSequences++;
	}
	senderBuffer = { "00000000" };							//Her laves probing headeren
	senderBuffer[0] += "001";
	senderBuffer[0] += intToString(numberOfSequences);

	for (size_t i = 1; i <= numberOfSequences; i++)			//Der laves headeren til hvert segment
	{														
		senderBuffer.push_back(intToString(i));
		if (i<numberOfSequences)
		{
			senderBuffer[i] += "000";
		}
		else
		{
			senderBuffer[i] += "100";
		}
		for (size_t k = 0; k < 80; k++)
		{															
			if (enTekst.size() == k + 80 * i - 80)						//Hvis et segment er mindre end 80 byte,
			{												//så der ikke mere at sende i det segment
				break;
			}
			senderBuffer[i] += enTekst[k+80*i-80];	
		}
	}

	//-----------------------------------------------

	for (size_t i = 0; i < senderBuffer.size(); i++)
	{
		std::cout << senderBuffer[i] << std::endl;
		sendSegment(senderBuffer[i]);
		//std::string somestuff = waitForACK();
	
	}
	
	//-----------------------------------------------
	
	

}

std::string Transportlag::intToString(int talTilKonvertering)
{
	std::string binary = "";
	for (int i = 1; i <= 8; i++)
	{
		if (std::bitset<8>(talTilKonvertering)[8 - i] == 1)
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

void Transportlag::sendSegment(std::string etSegment)
{
	dll.applySenderDLL(etSegment);
}

std::string Transportlag::waitForACK()
{
	return dll.applyRecieverDLL();

}

std::string Transportlag::receiverTransport()
{
	return "";
}
