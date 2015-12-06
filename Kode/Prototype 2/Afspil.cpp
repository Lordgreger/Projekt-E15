#include "Afspil.h"


Afspil::Afspil()
{
}

Afspil::~Afspil()
{
}


void Afspil::sendData(std::vector<int> input)
{
	addToner(input);
	makeRaw0(input.size());
	afspilToner();
}

void Afspil::addToner(std::vector<int> input)
{
	for (size_t i = 0; i < input.size(); i++)
	{
	tonerTilAfspilning.push_back(dtmfToner[input[i]]);
	}
}
	
void Afspil::makeRaw0(int lenght)
{
	for (int k = 0; k < dtmfToner.size(); k++)
	{
		for (int i = 0; i < ((dtmfToner[k]->getRaw()).size())/lenght; i++)
		{
			raw0.push_back((dtmfToner[k]->getRaw())[i]);
		}
	//std::cout << k << std::endl;
	//std::cout << raw0.size() << std::endl;
	}
}

int Afspil::afspilToner()
{
	sf::SoundBuffer Buffer;						//Vi opretter et Buffer objekt
	if (!Buffer.loadFromSamples					//Bufferen loades med vores sinus kurve, antalet af samples, 
		(&raw0[0], SAMPLES, 1, SAMPLE_RATE))		//kanaler (1 = mono), og sample rate
	{
		std::cerr << "Loading failed!" << std::endl;
		return 1;								//Siger der er fejl hvis det ikke kan lade sig gøre
	}

	sf::Sound Sound;							//Vi opretter et Sound objekt
	Sound.setBuffer(Buffer);					//Her sættes soundobjektes buffer
												//Vi looper objektet
	Sound.play();								//Vi afspiller objektet

	sf::sleep(sf::milliseconds(4050));
	

	
	return 0;
}
