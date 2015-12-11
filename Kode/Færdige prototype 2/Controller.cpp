#include "Controller.h"


Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::sendBesked(std::string besked, std::string uName)
{
	std::string tempBesked = uName + ": " + besked;
	CharDeff.applyCharDef(tempBesked);
	Files historik(uName);
	historik.AddNewLine(tempBesked);
	historik.~Files();
}

std::string Controller::modtagBesked(std::string uName)
{
	std::string besked = CharDeff.recieverCharDef();
	Files historik(uName);
	historik.AddNewLine(besked);
	historik.~Files();
	return besked;
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
