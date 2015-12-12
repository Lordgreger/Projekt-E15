#include "Login.h"



Login::Login()
{
}

Login::~Login()
{
}

bool Login::testLogin(std::string uName, std::string pWord)
{
	return (validateLogin(uName, pWord)); //Der kaldes på en validering af login
}

void Login::addUser(std::string uName, std::string pWord)
{
	std::ofstream addUser("loginDB.txt", std::ios::app); //Åbn loginDB i append mode

	addUser << uName << " " << pWord << std::endl; //Append ny bruger data i slutningen af loginDB

	addUser.close(); //Luk filen loginDB
}

bool Login::validateLogin(std::string useName, std::string pasWord)
{
	std::string token = useName + " " + pasWord; //Der oprettes en token ud fra username og password
	std::string tempString; //Der laves en temporary string til at holde linjer fra loginDB
	std::ifstream file("loginDB.txt"); //loginDB åbnes så den kan læses
	while (getline(file, tempString)) //Der andvendes getline til at hente en hel linje og gemme den i tempString
	{
		if (token == tempString) //Der token sammenlignes med tempString
			return 1; //hvis true retuner true
	}
	return 0; //Hvis ingen passer returner false
}
