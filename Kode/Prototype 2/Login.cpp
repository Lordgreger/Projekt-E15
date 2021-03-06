#include "Login.h"



Login::Login()
{
}

Login::~Login()
{
}

bool Login::testLogin(std::string uName, std::string pWord)
{
	return (validateLogin(uName, pWord)); //Der kaldes p� en validering af login
}

void Login::addUser(std::string uName, std::string pWord)
{
	if (testUser(uName) == 1)
	{
		std::cout << "Brugernavn er taget" << std::endl;
	}

	else
	{
		std::ofstream addUser("loginDB.txt", std::ios::app); //�bn loginDB i append mode

		addUser << uName << " " << pWord << std::endl; //Append ny bruger data i slutningen af loginDB

		addUser.close(); //Luk filen loginDB

		std::cout << "Bruger blev oprettet" << std::endl;

	}
}

bool Login::validateLogin(std::string useName, std::string pasWord)
{
	std::string token = useName + " " + pasWord; //Der oprettes en token ud fra username og password
	std::string tempString; //Der laves en temporary string til at holde linjer fra loginDB
	std::ifstream file("loginDB.txt"); //loginDB �bnes s� den kan l�ses
	while (getline(file, tempString)) //Der andvendes getline til at hente en hel linje og gemme den i tempString
	{
		if (token == tempString) //Der token sammenlignes med tempString
			return 1; //hvis true retuner true
	}
	return 0; //Hvis ingen passer returner false
}

bool Login::testUser(std::string useName)
{
	std::string userName = useName;			//Henter username
	std::string tempString;					//Der laves en temporary string til at holde info fra loginDB

	std::ifstream file("loginDB.txt");		//loginDB �bnes
	while (getline(file, tempString))		//Der anvendes getline til at hente hver token
	{
											//extract the first word
		std::stringstream stream(tempString);
		stream >> tempString;


		if (userName == tempString)			//Username sammenlignes med tempString
			return 1;						//Returnerer true hvis username er taget
	}
	return 0;								//Returnerer false hvis username er ledigt
}