#include "MyRecorder.h"



MyRecorder::MyRecorder()
{	
}

bool MyRecorder::onStart()
{
	resultatVektor = { 16 };
	beskedBegyndt = false;
	setProcessingInterval(sf::milliseconds(10));
	return true;
}

bool MyRecorder::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount)
{
	if (beskedBegyndt == false)
	{
		sf::sleep(sf::milliseconds(50));
	}
	
	unsigned int currentTone = goertzel.findTone(samples);

	if (currentTone == 16)
	{
		return true;
	}

	if (!(debounceBuffer1 == debounceBuffer2 && debounceBuffer1 == currentTone && debounceBuffer2 == currentTone))
	{
		debounceBuffer2 = debounceBuffer1;
		debounceBuffer1 = currentTone;
		//std::cout << currentTone << " " << debounceBuffer1 << " " << debounceBuffer2 << std::endl;
		return true;
	}

	std::cout << currentTone << " " << debounceBuffer1 << " " << debounceBuffer2 << std::endl;
	//std::cout << currentTone << std::endl;

	if (currentTone == 15)										//15 er startbitbit(tone)
	{
		debounceBuffer2 = debounceBuffer1;
		debounceBuffer1 = currentTone;
		beskedBegyndt = true;
		return true;
	}
	
	if (currentTone == 14)										//14 er slutbit(tone)
	{
		debounceBuffer2 = debounceBuffer1;
		debounceBuffer1 = currentTone;
		nyBesked = true;
		return false;
	}

	if (beskedBegyndt)
	{
		if (resultatVektor.back() != currentTone)
		{
			//std::cout << currentTone << std::endl;
			resultatVektor.push_back(currentTone);
		}
	}

	debounceBuffer2 = debounceBuffer1;
	debounceBuffer1 = currentTone;

	//std::cout << currentTone << std::endl;
	
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
