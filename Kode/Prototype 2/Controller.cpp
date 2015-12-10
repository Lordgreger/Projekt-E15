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

bool Controller::testLogin(std::string uName, std::string pWord)
{
	if (login.testLogin(uName, pWord))
		return true;
	return false;
}

void Controller::createUser(std::string uName, std::string pWord)
{
	login.addUser(uName, pWord);
}

void Controller::gethistory(std::string uName)
{
	Files historik(uName);
	historik.UpdateVector();
	historik.PrintVector();
}
