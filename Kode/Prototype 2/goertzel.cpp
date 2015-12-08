#include "goertzel.h"



Goertzel::Goertzel()
{
}

int Goertzel::findTone(const sf::Int16* samples)
{
	int resultArrayA[4] = {};
	int resultArrayB[4] = {};

	for (int i = 0; i < 4; i++)
	{
		resultArrayA[i] = detectFreqs(samples, kTone1[i]);
	}

	for (int m = 0; m < 4; m++)
	{
		resultArrayB[m] = detectFreqs(samples, kTone2[m]);
	}

	int max[2] = {};
	int y = 0;

	for (int i = 0; i < 4; i++)
	{
		if (y < resultArrayA[i])
		{
			y = resultArrayA[i];
			max[0] = i;
		}
	}

	y = 150000;

	for (int i = 0; i < 4; i++)
	{
		if (y < resultArrayB[i])
		{
			y = resultArrayB[i];
			max[1] = i;
		}
	}
		
	/*for (size_t i = 0; i < 4; i++)
	{
		std::cout << resultArrayB[i] << std::endl;
	}*/

	if (y > 150000 )
	{	
		
	//	std::cout << max[1] + (max[0]) * 4 << "      " << y << std::endl;
		return max[1] + (max[0]) * 4;
		
	}
	
	return 16;
}


int Goertzel::findTones(const sf::Int16* samples)
{
	int resultArrayA[4];
	int resultArrayB[4];

	for (int i = 0; i < 4; i++)
	{
		resultArrayA[i] = detectFreqs(samples, kTone1[i]);
	}

	for (int m = 0; m < 4; m++)
	{
		resultArrayB[m] = detectFreqs(samples, kTone2[m]);
	}

	int max[2] = { 0,0 };
	int y = 0;
	int x = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int n = i + 1; n < 4; n++)
		{
			x++;
			if (y < resultArrayA[i] + resultArrayA[n])
			{
				y = resultArrayA[i] + resultArrayA[n];
				max[0] = x;
			}
		}
	}

	y = 0;
	x = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int n = i + 1; n < 4; n++)
		{
			x++;
			if (y < resultArrayB[i] + resultArrayB[n])
			{
				y = resultArrayB[i] + resultArrayB[n];
				max[1] = x;
			}
		}
	}





	return max[0] + (max[1] - 1) * 6;

}


int Goertzel::detectFreqs(const sf::Int16* samples, int K)
{
	

	double f = K / (double)N;
	double omega = 2 * pi * f;
	double s = 0;
	double prevS1 = 0;
	double prevS2 = 0;
	

	for (int i = 0; i < N; i++)
	{
		s = samples[i] + 2 * cos(omega) * prevS1 - prevS2;
		prevS2 = prevS1;
		prevS1 = s;
	}

	int power = prevS2*prevS2 + prevS1*prevS1 - 2 * cos(omega)*prevS1*prevS2;
	power = pow(power, 2) / 20000000000;
	
	return power;
	


}





Goertzel::~Goertzel()
{
}