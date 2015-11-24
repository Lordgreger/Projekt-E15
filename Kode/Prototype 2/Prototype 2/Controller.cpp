#include "Controller.h"


Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::sendBesked(std::string besked)
{
	besked = CharDeff.charToBinary(besked);

	besked = DLL.applySenderDLL(besked);

	std::vector<int> beskedLyd = ToneKonvertering.konverterTilLyd(besked);

}

void Controller::modtagBesked()
{

}
