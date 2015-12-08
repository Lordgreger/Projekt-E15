#include "Controller.h"


Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::sendBesked(std::string besked)
{
	CharDeff.applyCharDef(besked);
}

std::string Controller::modtagBesked()
{
	return CharDeff.recieverCharDef();
}
