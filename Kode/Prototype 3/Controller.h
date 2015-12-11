#pragma once
#include "CharDefinition.h"
#include "Login.h"
#include "Files.h"
#include <string>


class Controller
{
public:
	Controller();
	~Controller();

	void sendBesked(std::string besked, std::string uName);
	std::string modtagBesked();
	bool testLogin(std::string uName, std::string pWord);
	void createUser(std::string uName, std::string pWord);
	void getHeleHistory(std::string uName);
	void getSenesteHistory(std::string uName);
	void getDefinedHistory(std::string uName, int x, int y);

protected:
	CharDefinition CharDeff;
	Login login;

};