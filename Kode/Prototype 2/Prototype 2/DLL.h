#pragma once
#include "CRC.h"

class DLL
{
public:
	DLL();
	~DLL();

	std::string applySenderDLL(std::string bitstreng);				//Tilf�jer CRC og stuffing til bitstreng
	std::string applyRecieverDLL(std::string bitstreng);			//Returnerer string ved korrekt CRC, ellers error 1

protected:
	std::string stuffing(std::string bitstreng);					//Tilf�jer stuffing
	std::string removeStuffing(std::string bitstreng);				//Fjerner stuffing

	CRC CRC;														//CRC objekt for at udf�re CRC udregning
};