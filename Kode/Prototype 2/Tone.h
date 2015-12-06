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

	Tone(int fekvens1);
	Tone(int fekvens1, int fekvens2);  //Denne kode afspiller DTMF tone, givet ved f1 og f2
	std::vector <sf::Int16> getRaw();

protected:
	const unsigned SAMPLES = 44100;
	const unsigned SAMPLE_RATE = 44100;
	std::vector <sf::Int16>  raw1;
	int f1;
	int f2;
};

