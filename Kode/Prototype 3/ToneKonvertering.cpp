#include "ToneKonvertering.h"


ToneKonvertering::ToneKonvertering()
{
}

ToneKonvertering::~ToneKonvertering()
{
}


void ToneKonvertering::applyToneKonv(std::string input)
{
	std::vector<int> temp = konverterTilLyd(input);
	play.sendData(temp);
}

std::string ToneKonvertering::returnBitString()
{
	sf::Clock clock;
	sf::Time tid;
	bool clockReset = false;
	if (!MyRecorder::isAvailable())							//Tjekker om der er en mic
	{
		std::cout << "fix mic";
	}
	optag.start(8000);
	while (!optag.getNyBesked() && tid.asSeconds() < 10 )
	{
		
		if (optag.getBeskedBegyndt() && !clockReset)
		{
			clock.restart();
			clockReset = true;

			//std::cout << "    " << std::endl;

		}
		tid = clock.getElapsedTime();
	}
	optag.stop();

	if (!optag.getNyBesked())
	{
		return "Fejl: No message!";
	}

	vector<int> output = optag.getBesked();
	

	output.erase(output.begin());

	//for (size_t i = 0; i < output.size(); i++)
	//{
	//	std::cout << output[i] << std::endl;
	//}

	//std::cout << output.size() << std::endl;

	return konverterTilBit(output);
}

std::vector<int> ToneKonvertering::konverterTilLyd(std::string bitstreng)
{
	std::vector<int> output = { 15 }; 					//Der laves en dataholder til output
	std::string tempString;								//tempString bruges til midlertidig dataholder til s�t af bitstreng
	int i = 0;											//Index s�ttes til 0
	while (i < bitstreng.length())						//N�r i er mindre end l�ngden af bitstreng k�res for loopet
	{

		tempString = "";								//tempString resettes n�r while starter

		for (size_t x = 0; x < 3; x++)					//S�tter 3 karakterer fra bitstreng til tempString
		{
			tempString = tempString + bitstreng[i];		//L�gger 1 enhed fra bitstreng til tempString
			i++;										//Inkrementerer indexet
		}

		for (size_t y = 0; y < 8; y++)					//Tjekker de 8 forskellige kombinationer igennem og finder hvilken er lig tempString
		{
			if (tempString == stringDef[y])				//Tester om tempString er lig en bestemt position p� StringDef
			{	
				if (output.size() > 0)					//Tjekker om der er noget gemt i outputet (laver en fejl ellers ved .back())
				{
					if (y == output.back())				//Tester om tonen er den samme som den forrige
					{
					output.push_back(8);				//Inds�tter et tone flag istedet for den samme tone
					break;
					}
				}
				output.push_back(y);					//Hvis tempString er lig StringDef, tempString ligges bag p� output
				break;									//Stopper for l�kken
			}
		}
	}
	output.push_back(14);

	//for (size_t i = 0; i < output.size(); i++)
	//{
	//	std::cout << output[i] << std::endl;
	//}

	return output;
}

std::string ToneKonvertering::konverterTilBit(std::vector<int> input)
{
	std::string output;

	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] == 8)
		{
			output.append(stringDef[input[i-1]]);
		}
		else
			output.append(stringDef[input[i]]);
	}

	return output;
}