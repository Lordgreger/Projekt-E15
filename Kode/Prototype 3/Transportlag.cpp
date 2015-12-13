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
	//Initializer


	numberOfSequences = enTekst.size() / 80;					//Find antal segmenter der skal sendes

	if (enTekst.size() % 80 != 0)
	{
		numberOfSequences++;									//Én lægges til hvis der ikke sendes et antal bytes der går op i 10.
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

	for (size_t i = 0; i <= numberOfSequences; i++)							//Nu sender vi segmenterne og modtager ACK
	{
		std::cout << "Vi sender sekvens nummer: " << i + 1 << std::endl;
		//---------------------------------------------

		for (size_t k = 0; k < 5; k++)										//Vi sender højst et segment 5 gange
		{
			//std::cout << "sender " << senderBuffer[i] << std::endl;
			sendSegment(senderBuffer[i]);

			receiverBuffer[i] = waitForMessage();	

			//std::cout << "modtog " << receiverBuffer[i] << std::endl;
			if (receiverBuffer[i] == "Fejl: No message!")					//Hvis vi modtager en fejlmeddelelse (tom eller CRC fejl)
			{
				std::cout << "Vi fandt en fejl i ACK!!!" << std::endl;
				if (k == 2 && i == 0)										//Hvis vi fejler vores probing 3 gange giver vi op
				{
					return "Fejl: No connection created!";
				}
				else if (k == 4)											//Hvis vi ikke modtager et ACK 5 gange giver vi op
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

		if (i == 0 && receiverBuffer[i] == "00000000000")					//Hvis Kontrol flag for accept er ikke sat-
		{
			return "Receiver does not accept message!";						//Så accepterer modtageren ikke, og vi stopper
		}

		if (i != binaryToDecimal(receiverBuffer[i].substr(0, 8)))
		{
			i = i--;														//Hvis ACK ikke passer overens sendes det sidste segment igen..
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
	//Initialize

	senderBuffer[0] = "00000000010";															// Probing ACK
	for (size_t i = 1; i < 256; i++)															// Vi laver resten af ACK'erne
	{
		senderBuffer[i] = intToString(i);														// ACK nummer
		senderBuffer[i] += "000";																// Control flag
	}

	for (size_t i = 0; i <= numberOfSequences; i++)												//Vi sidder og modtager beskeder, og sender ACK tilbage.
	{
		if (i == 0)																				//Special case: Probing svar
		{
			for (size_t k = 0; k < 10; k++)														//Vi giver senderen 10 forsøg til at probe (altså 10 gange optagelsestiden)
			{

				receiverBuffer[0] = waitForMessage();											//Optag


				if (receiverBuffer[0] != "Fejl: No message!")									//Hvis vi modtager en besked-
				{
					if ("001" == receiverBuffer[0].substr(8, 3))								//Checker vi om det er en probing
					{
						numberOfSequences = binaryToDecimal(receiverBuffer[0].substr(11, 8));	//Hvis det er en probing, aflæser vi antal segmenter der sendes
						break;
					}
				}
				if (k == 9)																		//vi modtog ikke noget 10 gange
				{
					return "Fejl: No message!";
				}
			}
		sendSegment(senderBuffer[0]);															//Send ACK for probing
		}

		else																					//hvis forbindelsen er oprettet
		{
			for (size_t k = 0; k < 3; k++)														//Hver gang vi modtager forsøger vi 3 gange, ellers er forbindelsen tabt
			{
				receiverBuffer[i] = waitForMessage();											//Modtag
				
				if (receiverBuffer[i] != "Fejl: No message!")									//Hvis vi modtager noget
				{

					if (receiverBuffer[i].substr(0,8) != senderBuffer[i].substr(0,8))			//Checker vi ACK og sekvens nummer
					{
						i--;																	//hvis de er forskellige sendes forrige ACK igen
					}
					break;
				}
				if (k == 2)																		//Efter 3 forsøg er forbindelsen tabt
				{
					return "Fejl: Connection lost!";
				}
			}
			
			sendSegment(senderBuffer[i]);														//Send ACK
			
		}
		if (receiverBuffer[i][8] == '1')														//Check for slut flag
		{
			for (size_t k = 0; k < 3; k++)														//3 forsøg til at modtage
			{
				if (waitForMessage() == "Fejl: No message!")
				{
					break;
				}
				
				sendSegment(senderBuffer[i]);
				
			}
			break;
		}
	}

	std::string message;	
	
	for (size_t i = 1; i <= numberOfSequences; i++)								//Omdan buffer til besked og retuner den til CharDef
	{
		receiverBuffer[i].erase(0, 11);											//Fjern header
		message += receiverBuffer[i];
	}
	return message;
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


