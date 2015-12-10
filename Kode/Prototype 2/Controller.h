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

	void sendBesked(std::string besked);
	std::string modtagBesked();
	bool testLogin(std::string uName, std::string pWord);
	void createUser(std::string uName, std::string pWord);
	void gethistory(std::string uName);

protected:
	CharDefinition CharDeff;
	Login login;

};