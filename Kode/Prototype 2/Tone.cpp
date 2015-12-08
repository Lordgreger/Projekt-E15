#include "Tone.h"


Tone::Tone()
{
}

Tone::~Tone()
{
}

Tone::Tone(int fekvens1)
{
	f1 = fekvens1;
	f2 = 0;
}

Tone::Tone(int fekvens1, int fekvens2)
{
	f1 = fekvens1;
	f2 = fekvens2;


	const unsigned SAMPLES = 5113;				//Antallet af samples skal matche sample rate, fordi vi sampler over 1 sekund 
	const unsigned SAMPLE_RATE = 44100;			//Standard sampling rate for cd'er
	const unsigned AMPLITUDE = 10000;			//Der skal være en amplitude for volume
												//maks 32767/2 fordi vi har et 16 signed array, og 2 bøgler lagt sammen må maks give 32767

												//16bit array oprettes til at holde den samplede data

	const double TWO_PI = 6.28318;
	
	
	//Der genereres en samplet sinus kurve med 2 frekvenser, som gemmes i vectoren
	for (unsigned i = 0; i < SAMPLES; i++)
	{
		raw1.push_back( AMPLITUDE*(sin(f1 * TWO_PI * i / SAMPLE_RATE) +sin(f2 * TWO_PI * i / SAMPLE_RATE)));
	}
	
}

std::vector <sf::Int16> Tone::getRaw()
{
	return raw1;
}
