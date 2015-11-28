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

void Controller::modtagBesked()
{

}
