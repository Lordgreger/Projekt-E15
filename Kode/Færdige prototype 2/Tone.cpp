#include "Tone.h"


Tone::Tone()
{
}

Tone::~Tone()
{
}

Tone::Tone(int fekvens1, int fekvens2)
{
	f1 = fekvens1;
	f2 = fekvens2;

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
