#pragma once
#include "CharDefinition.h"
#include "DLL.h"
#include "ToneKonvertering.h"
#include <string>


class Controller
{
public:
	Controller();
	~Controller();

	void sendBesked(std::string besked);
	std::string modtagBesked();

private:
	CharDefinition CharDeff;

};