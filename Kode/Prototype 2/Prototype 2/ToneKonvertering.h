#pragma once
#include <vector>
#include <string>

class ToneKonvertering
{
public:
	ToneKonvertering();
	~ToneKonvertering();

	std::vector<int> konverterTilLyd(std::string bitstreng);		//Konverterer en string af bits til en vector af toner
	std::string konverterTilBit(std::vector<int> input);			//Konverterer en vector af toner til en string af bits

protected:
	std::string stringDef[8] = { "000","001","010","011","100","101","110","111" }; //De forskellige bin�re kombinationer
};