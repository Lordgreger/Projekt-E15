#include "MyRecorder.h"



MyRecorder::MyRecorder()
{	
}

bool MyRecorder::onStart()
{
	beskedBegyndt = false;
	setProcessingInterval(sf::milliseconds(25));
	return true;
}

bool MyRecorder::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount)
{
	if (beskedBegyndt == false)
	{
		sf::sleep(sf::milliseconds(50));
	}
	
	int currentTone = goertzel.findTone(samples);

	if (currentTone == 15)										//15 er startbitbit(tone)
	{
		resultatVektor = {0};
		beskedBegyndt = true;
		return true;
	}
	
	if (currentTone == 14)										//14 er slutbit(tone)
	{
		nyBesked = true;
	//	resultatVektor.erase(resultatVektor.begin());
		return false;
	}
	
	if (currentTone == 16)
	{
		return true;
	}

	if (beskedBegyndt)
	{
		if (resultatVektor.back() != currentTone)
		{
			resultatVektor.push_back(currentTone);
		}
	}

	std::cout << currentTone << std::endl;
	
	return true;
}

void MyRecorder::onStop()
{

}


vector<int> MyRecorder::getBesked()
{	
	nyBesked = false;
	return resultatVektor;
}

bool MyRecorder::getNyBesked()
{
	return nyBesked;
}


MyRecorder::~MyRecorder()
{
}
