#pragma once
#include <cmath>
#include "SFML\Audio.hpp"

class Goertzel
{
public:
	Goertzel();

	int findFreq(const sf::Int16* samples);
	int findFreqs(const sf::Int16* samples);
	int detectFreqs(const sf::Int16* samples, int K);

	~Goertzel();

protected:
	const double pi = 3.1415926;
	const int N = 300;
	int x = 0;
	const int kTone1[4] = { 26, 29 ,32, 35 };
	const int kTone2[4] = { 45, 50, 55, 61 };
};