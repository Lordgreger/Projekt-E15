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
	
	virtual bool onStart();

	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);

	virtual void onStop();

	vector<int> getBesked();

	~MyRecorder();

protected:
	bool beskedBegyndt = false;
	bool nyBesked = false;
	vector<int> resultatVektor = {0};
	vector<int> ikkeKlar = {0};
	Goertzel lort;
	
};
