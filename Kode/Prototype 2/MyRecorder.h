#pragma once
#include "SFML\Audio.hpp"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "goertzel.h"

class MyRecorder : public sf::SoundRecorder
{
public:
	MyRecorder();
	~MyRecorder();

	vector<int> getBesked();
	bool getNyBesked();

protected:
	virtual bool onStart();
	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
	virtual void onStop();

	bool beskedBegyndt = false;
	bool nyBesked = false;
	vector<int> resultatVektor = {0};
	Goertzel goertzel;
	
};
