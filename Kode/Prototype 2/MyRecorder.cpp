#include "MyRecorder.h"



MyRecorder::MyRecorder()
{	
}

bool MyRecorder::onStart()
{
	
	setProcessingInterval(sf::milliseconds(25));
	return true;
}

bool MyRecorder::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount)
{
	if (beskedBegyndt == false)
	{
		sf::sleep(sf::milliseconds(50));
	}
	
	int currentTone = lort.findTone(samples);
		

	if (currentTone == 15)										//15 er startbitbit(tone)
	{
		resultatVektor = {0};
		beskedBegyndt = true;
		return true;
	}
	if (currentTone == 14)										//14 er slutbit(tone)
	{
		beskedBegyndt = false;
		nyBesked = true;
		return false;
	}
	if (beskedBegyndt)
	{
		resultatVektor.push_back(currentTone);
	}	
	
	if (currentTone == 16 )
	{
		return true;
	}
	std::cout << currentTone << std::endl;
	
	return true;
}

void MyRecorder::onStop()
{

}


vector<int> MyRecorder::getBesked()
{	
	if (beskedBegyndt == false && nyBesked == true)
	{
		nyBesked = false;
		return resultatVektor;
	}
	return ikkeKlar;
}


MyRecorder::~MyRecorder()
{
}
