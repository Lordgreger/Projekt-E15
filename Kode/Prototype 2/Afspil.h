#pragma once
#include <SFML/Audio.hpp>
#include "Tone.h"
#include <iostream>
#include <vector>

class Afspil
{
public:
	Afspil();
	~Afspil();

	void sendData(std::vector<int> input);

protected:
	void addToner(std::vector<int> input);
	void makeRaw0(std::vector<int> input);
	int afspilToner(int længdeAfElementer);

	std::vector<Tone*> dtmfToner = { new Tone(697, 1209), new Tone(697, 1336), new Tone(697, 1477), new Tone(697, 1633),
									 new Tone(770, 1209), new Tone(770, 1336), new Tone(770, 1477), new Tone(770, 1633),
									 new Tone(852, 1209), new Tone(852, 1336), new Tone(852, 1477), new Tone(852, 1633),
									 new Tone(941, 1209), new Tone(941, 1336), new Tone(941, 1477), new Tone(941, 1633),
									 new Tone(0,0)};
	std::vector<Tone*> tonerTilAfspilning;
	const unsigned SAMPLES = 1000;
	const unsigned SAMPLE_RATE = 8000;
	std::vector <sf::Int16>  raw0 = {0};
};

