#include "Transportlag.h"

Transportlag::Transportlag()
{
}

Transportlag::~Transportlag()
{
}

std::string Transportlag::senderTransport(std::string enTekst)
{
	receiverBuffer.clear();
	receiverBuffer.resize(256);
	senderBuffer.clear();
	senderBuffer.resize(256);
	numberOfSequences = enTekst.size() / 80;

	if (enTekst.size() % 80 != 0)
	{
		numberOfSequences++;
	}
	senderBuffer[0] = { "00000000" };							//Her laves probing headeren
	senderBuffer[0] += "001";
	senderBuffer[0] += intToString(numberOfSequences);

	for (size_t i = 1; i <= numberOfSequences; i++)				//Der laves headeren til hvert segment
	{
		senderBuffer[i] = intToString(i);						//sequence number indsættes
		if (i<numberOfSequences)
		{
			senderBuffer[i] += "000";							//kontrol flags indsættes
		}
		else
		{
			senderBuffer[i] += "100";							//kontrol flag sidste besked flagget sættes
		}
		for (size_t k = 0; k < 80; k++)
		{
			if (enTekst.size() == k + 80 * i - 80)				//Hvis et segment er mindre end 80 byte,
			{													//så der ikke mere at sende i det segment
				break;
			}
			senderBuffer[i] += enTekst[k + 80 * i - 80];
		}
	}

	//-----------------------------------------------

	for (size_t i = 0; i <= numberOfSequences; i++)
	{
		

		//---------------------------------------------
		for (size_t k = 0; k < 5; k++)
		{
			//std::cout << "sender " << senderBuffer[i] << std::endl;
			sendSegment(senderBuffer[i]);

			receiverBuffer[i] = waitForMessage();							//Prøv igen
			//std::cout << "modtog " << receiverBuffer[i] << std::endl;
			if (receiverBuffer[i] == "Fejl: No message!")				//Hvis vi modtager en fejlmeddelelse (tom eller CRC fejl)
			{

				if (k == 2 && i == 0)										//Hvis vi fejler vores probing 3 gange giver vi op
				{
					return "Fejl: No connection created!";
				}
				else if (k == 4)										//Hvis vi ikke modtager et ACK 5 gange giver vi op
				{
					return "Fejl: Connection lost!";
				}

			}
			else
			{
				break;
			}
		}
		//---------------------------------------------

		if (i == 0 && receiverBuffer[i] == "00000000000")
		{
			return "Receiver does not accept message!";								//Hvis modtageren ikke accepter stopper vi
		}

		if (i != binaryToDecimal(receiverBuffer[i].substr(0, 8)))
		{
			//std::cout << "indeks er " << i << " vi tjekker imod " << binaryToDecimal(receiverBuffer[i].substr(0, 8)) << std::endl;
			i = i--;									//Hvis ACK ikke passer overens sendes det sidste segment igen..
		}


	}

	//-----------------------------------------------	



	return "Message delivered!";

}



std::string Transportlag::receiverTransport()
{
	receiverBuffer.clear();
	receiverBuffer.resize(256);
	senderBuffer.clear();
	senderBuffer.resize(256);
	int numberOfSequences = 256;
	senderBuffer[0] = "00000000010";							// Probing ACK
	for (size_t i = 1; i < 256; i++)				// Vi definerer senderbufferen
	{
		senderBuffer[i] = intToString(i);						// ACK nummer
		senderBuffer[i] += "000";								// Control flag
	}

	for (size_t i = 0; i <= numberOfSequences; i++)
	{
		if (i == 0)
		{
			for (size_t k = 0; k < 10; k++)
			{
				receiverBuffer[0] = waitForMessage();

				if (receiverBuffer[0] != "Fejl: No message!")
				{

					if ("001" == receiverBuffer[0].substr(8, 3))
					{
						numberOfSequences = binaryToDecimal(receiverBuffer[0].substr(11, 8));
						break;
					}
				}
				if (k == 9)
				{
					return "Fejl: No message!";
				}
			}
		sendSegment(senderBuffer[0]);

		}
		else
		{
			for (size_t k = 0; k < 3; k++)
			{
				receiverBuffer[i] = waitForMessage();
				if (receiverBuffer[i] != "Fejl: No message!")
				{
					if (receiverBuffer[i].substr(0,8) != senderBuffer[i].substr(0,8))
					{
						i--;
					}
					break;
				}
				if (k == 2)
				{
					
					return "Fejl: Connection lost!";
				}
			}
			sendSegment(senderBuffer[i]);
		}
		if (receiverBuffer[i][8] == '1')
		{
			break;
		}
	}


	std::string message;	
	//std::cout << "sequence number " << numberOfSequences << std::endl;

	for (size_t i = 1; i <= numberOfSequences; i++)
	{
		receiverBuffer[i].erase(0, 11);
		message += receiverBuffer[i];
	
	}

	return message;






/*

	for (size_t i = 0; i < 10; i++)
	{
		receiverBuffer[0] = waitForMessage();

		if (receiverBuffer[0] != "Fejl: No message!")
		{
			
			if ("001" == receiverBuffer[0].substr(8, 3))
			{
				numberOfSequences = 5;
				binaryToDecimal(receiverBuffer[0].substr(1, 8));
				break;
			}
		}
		if (i == 9)
		{
			return "Fejl: No message!";
		}
	}*/



	
/*

	for (size_t i = 0; i < numberOfSequences; i++)
	{
		std::cout << "sender " << senderBuffer[i] << std::endl;
		sendSegment(senderBuffer[i]);

		for (size_t k = 0; k < 10; k++)
		{		
			receiverBuffer[i] = waitForMessage();
			std::cout << "modtog " << receiverBuffer[i] << std::endl;

			if (receiverBuffer[i] == "Fejl: No message!" && k==9)
			{
				return "Fejl: Connection lost!";
			}
			else if(receiverBuffer[i] != "Fejl: No message!")
			{
				break;
			}
		}
		
		std::cout << receiverBuffer[i] << std::endl;
		std::cout << "diller loop " << binaryToDecimal(receiverBuffer[i].substr(0, 8)) << "tjekker imod " << i << std::endl;
		if (binaryToDecimal(receiverBuffer[i].substr(0, 8)) != i)
		{
			

			i--;
		}
			std::cout << i << std::endl;
	}

	std::string message;
	for (size_t i = 1; i < numberOfSequences; i++)
	{
		receiverBuffer[i].erase(0, 11);
		message += receiverBuffer[i];
	}

	return message;*/
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

int Transportlag::binaryToDecimal(std::string bins)
{

	int decimal = 0;

	for (int i = 0; i <= 7; i++)
	{
		if (bins[7-i] == '1')
		{
			decimal += pow(2 ,i);
		}
	}


	return decimal;
}

void Transportlag::sendSegment(std::string etSegment)
{
	dll.applySenderDLL(etSegment);
}

std::string Transportlag::waitForMessage()
{
	return dll.applyRecieverDLL();

}


