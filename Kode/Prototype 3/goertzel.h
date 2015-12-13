#pragma once
#include <string>
#include <iostream>
#include <cmath>
#include "SFML\Audio.hpp"
using namespace std;

class Goertzel
{
public:
	Goertzel();

	int findTone(const sf::Int16* samples);
	int findTones(const sf::Int16* samples);
	

	~Goertzel();

protected:
	int detectFreqs(const sf::Int16* samples, int K);
	const double pi = 3.1415926;
	const int N = 300;
	const int kTone1[4] = { 26, 29 ,32, 35 };
	const int kTone2[4] = { 45, 50, 55, 61 };

	


};