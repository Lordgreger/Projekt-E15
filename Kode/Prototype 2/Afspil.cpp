#include "Afspil.h"


Afspil::Afspil()
{
}

Afspil::~Afspil()
{
}


void Afspil::sendData(std::vector<int> input)
{
	//tonerTilAfspilning;
	//addToner(input);
	makeRaw0(input);
	afspilToner(input.size());
}

void Afspil::addToner(std::vector<int> input)
{
	for (size_t i = 0; i < input.size(); i++)
	{
	tonerTilAfspilning.push_back(dtmfToner[input[i]]);
	}
}
	
void Afspil::makeRaw0(std::vector<int> input)
{
	for (int k = 0; k < input.size(); k++)
	{
		for (int i = 0; i < ((dtmfToner[input[k]]->getRaw()).size())/8; i++)
		{
			raw0.push_back((dtmfToner[input[k]]->getRaw())[i]);
		}
	}
}

int Afspil::afspilToner(int længdeAfElementer)
{
	sf::SoundBuffer Buffer;						//Vi opretter et Buffer objekt
	if (!Buffer.loadFromSamples					//Bufferen loades med vores sinus kurve, antalet af samples, 
		(&raw0[0], længdeAfElementer * 5512.5, 1, SAMPLE_RATE))		//kanaler (1 = mono), og sample rate
	{
		std::cerr << "Loading failed!" << std::endl;
		return 1;								//Siger der er fejl hvis det ikke kan lade sig gøre
	}

	sf::Sound Sound;							//Vi opretter et Sound objekt
	Sound.setBuffer(Buffer);					//Her sættes soundobjektes buffer
												//Vi looper objektet
	Sound.play();								//Vi afspiller objektet

	sf::sleep(sf::seconds((længdeAfElementer * 5512.5)/ SAMPLE_RATE + 0.020));
	
	
	return 0;
}
