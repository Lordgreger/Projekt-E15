#pragma once
#include "Afspil.h"
#include "MyRecorder.h"
#include <vector>
#include <string>

class ToneKonvertering
{
public:
	ToneKonvertering();
	~ToneKonvertering();

	void applyToneKonv(std::string input);
	std::string returnBitString();

protected:
	std::vector<int> konverterTilLyd(std::string bitstreng);		//Konverterer en string af bits til en vector af toner
	std::string konverterTilBit(std::vector<int> input);			//Konverterer en vector af toner til en string af bits

	std::string stringDef[8] = { "000","001","010","011","100","101","110","111" }; //De forskellige binære kombinationer
	Afspil play;
	MyRecorder optag;
};