#pragma once
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include <vector>

class Tone
{
public:
	Tone();
	~Tone();

	Tone(int fekvens1, int fekvens2);  //Denne kode afspiller DTMF tone, givet ved f1 og f2
	std::vector <sf::Int16> getRaw();

protected:
	const unsigned SAMPLES = 1600;		//Forholdet af SAMPLES og SAMPLE_RATE skal passe i forhold til 1 sekund
	const unsigned SAMPLE_RATE = 8000;
	const unsigned AMPLITUDE = 5000;	//Der skal være en amplitude for volume
	const double TWO_PI = 6.28318;		//maks 32767/2 fordi vi har et 16 signed array, og 2 bøgler lagt sammen må maks give 32767
	std::vector <sf::Int16>  raw1;		//16bit array oprettes til at holde den samplede data
	int f1;
	int f2;
};

