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
	bool getBeskedBegyndt();

protected:
	virtual bool onStart();
	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
	virtual void onStop();

	bool beskedBegyndt = false;
	bool nyBesked = false;
	vector<int> resultatVektor = {16};
	int debounceBuffer1 = 16;
	int debounceBuffer2 = 16;
	Goertzel goertzel;
};
