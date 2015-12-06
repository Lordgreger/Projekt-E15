#include "DLL.h"
#include <iterator>


DLL::DLL()
{
}

DLL::~DLL()
{
}

std::string DLL::stuffing(std::string bitstreng)
{
	std::string stuffing = "";
	int tempInt = bitstreng.size();
	tempInt = tempInt % 3;

	if (tempInt == 0)
	{
		stuffing = "100";
	}

	if (tempInt == 1)
	{
		stuffing = "10";
	}

	if (tempInt == 2)
	{
		stuffing = "1";
	}

	bitstreng = bitstreng + stuffing;
	return bitstreng;
}

std::string DLL::removeStuffing(std::string bitstreng)
{
	while (true)
	{
		if (bitstreng.back() == '0')
		{
			bitstreng.pop_back();
		}
		if (bitstreng.back() == '1')
		{
			bitstreng.pop_back();
			break;
		}
	}
	return bitstreng;
}

void DLL::applySenderDLL(std::string bitstreng)
{
	bitstreng = bitstreng + CRC.runCRC(bitstreng);
	bitstreng = stuffing(bitstreng);
	//std::cout << bitstreng << std::endl;
	ToneKonv.applyToneKonv(bitstreng);
}

std::string DLL::applyRecieverDLL(std::string bitstreng)
{
	bitstreng = removeStuffing(bitstreng);	

	std::string tempCRC = "";

	tempCRC = tempCRC.append(bitstreng, bitstreng.size() - 32, 32);

	bitstreng.erase(bitstreng.size() - 32 , 32);

	if (CRC.runCRC(bitstreng) == tempCRC)
		return bitstreng;
	return "ERROR: CRC NOT TRUE";
}