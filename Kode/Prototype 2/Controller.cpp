#include "Controller.h"


Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::sendBesked(std::string besked, std::string uName)
{
	besked = uName + ": " + besked;
	CharDeff.applyCharDef(besked);
	Files historik(uName);
	historik.AddNewLine(besked);
	historik.~Files();
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

void Controller::getHeleHistory(std::string uName)
{
	Files historik(uName);
	historik.UpdateVector();
	historik.PrintVector();
	historik.~Files();
}

void Controller::getSenesteHistory(std::string uName)
{
	Files historik(uName);
	historik.UpdateVector();
	historik.PrintLatest();
	historik.~Files();
}

void Controller::getDefinedHistory(std::string uName, int x, int y)
{
	Files historik(uName);
	historik.UpdateVector();
	historik.PrintLines(x,y);
	historik.~Files();
}
