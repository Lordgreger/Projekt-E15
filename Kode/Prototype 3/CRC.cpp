#include "CRC.h"



CRC::CRC()
{
}


CRC::~CRC()
{
}

std::string CRC::runCRC(std::string message)
{
	std::string messageString = message;							//Original besked
	std::string poly = "111010101";									//Polynomial division

	std::string aug = messageString + "00000000";					//Padded besked, bliver senere til remainder indtil denne bliver checksummen
	std::string tempRemainderString;
	std::string tempAug;

	std::bitset<9> divisor(poly);									//Bit divisor
	std::bitset<9> tempRemainder;									//holder til besked

	while (aug.size() > 8)											//imens beskeden er st�rre end 8 (size of checksum!)
	{
		std::bitset<9> remainder(std::string(aug, 0, 9));			//Tag de 9 f�rste bit

		if (remainder[8] == 1)										//Hvis det f�rste bit er sat (!!! Dette l�ses bitvist, fra h�jre mod venstre!!!)
		{
			tempRemainder = remainder ^ divisor;					//Udf�r polynomial division via "xor"

			tempRemainderString = tempRemainder.to_string();
			tempAug = "";
			tempAug.append(aug, 9, aug.size());

			aug = tempRemainderString + tempAug;					//Saml resultat og resterende besked
		}
		else														//Hvis det f�rste bit ikke er sat, s� skal beskeden shiftes mod venstre
		{
			aug.erase(aug.begin());									//Sletter det f�rste bit i beskeden
		}
	}

	//std::cout << "checksum: " << aug << std::endl;					//Output checksum
	return aug;
}
