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

	while (aug.size() > 8)											//imens beskeden er større end 8 (size of checksum!)
	{
		std::bitset<9> remainder(std::string(aug, 0, 9));			//Tag de 9 første bit

		if (remainder[8] == 1)										//Hvis det første bit er sat (!!! Dette læses bitvist, fra højre mod venstre!!!)
		{
			tempRemainder = remainder ^ divisor;					//Udfør polynomial division via "xor"

			tempRemainderString = tempRemainder.to_string();
			tempAug = "";
			tempAug.append(aug, 9, aug.size());

			aug = tempRemainderString + tempAug;					//Saml resultat og resterende besked
		}
		else														//Hvis det første bit ikke er sat, så skal beskeden shiftes mod venstre
		{
			aug.erase(aug.begin());									//Sletter det første bit i beskeden
		}
	}

	//std::cout << "checksum: " << aug << std::endl;					//Output checksum
	return aug;
}
