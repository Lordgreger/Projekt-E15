#include "Controller.h"

int main()
{
	Controller controller;
	std::string user, pass, tempValg, tempValg2;

firstScreen:
	std::cout << "V\x91lg en operation" << std::endl;
	std::cout << "1. Login" << std::endl;
	std::cout << "2. Opret ny bruger" << std::endl;
	std::cin >> tempValg;

	if (tempValg == "1")
	{ 
		std::system("cls");
		goto loginScreen;
	}

	if (tempValg == "2")
	{ 
		std::system("cls");
		goto createUserScreen;
	}

	std::system("cls");
	goto firstScreen;


createUserScreen:
	std::cout << "Username?" << std::endl;
	std::cin >> user;
	std::cout << "Password?" << std::endl;
	std::cin >> pass;

	controller.createUser(user,pass);

	std::system("cls");
	goto firstScreen;


loginScreen:
	std::cout << "Username?" << std::endl;
	std::cin >> user;
	std::cout << "Password?" << std::endl;
	std::cin >> pass;

	if (controller.testLogin(user, pass))
	{ 
		std::system("cls");
		goto interfaceScreen;
	}

	std::system("cls");
	std::cout << "Forkert login" << std::endl;
	goto firstScreen;


interfaceScreen:
	std::cout << "V\x91lg en operation" << std::endl;
	std::cout << "1. Send besked" << std::endl;
	std::cout << "2. Modtag besked" << std::endl;
	std::cout << "3. Se historik" << std::endl;
	std::cout << "4. Log ud" << std::endl;
	std::cin >> tempValg;

	if (tempValg == "1")
	{ 
		std::system("cls");
		goto sendBeskedScreen;
	}

	if (tempValg == "2")
	{ 
		std::system("cls");
		goto modtagBeskedScreen;
	}

	if (tempValg == "3")
	{
		std::system("cls");
		goto historikScreen;
	}

	if (tempValg == "4")
	{ 
		user = "";
		pass = "";
		std::system("cls");
		goto firstScreen;
	}

	std::system("cls");
	goto interfaceScreen;


sendBeskedScreen:
	std::cout << "Indtast besked" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, tempValg);

	std::system("cls");
	std::cout << "Sender besked...";

	controller.sendBesked(tempValg, user);

	std::system("cls");
	goto interfaceScreen;


modtagBeskedScreen:
	tempValg2 = "";
	std::cout << "Modtager besked..." << std::endl;
	tempValg2 = controller.modtagBesked(user);
	std::system("cls");

modtagRepeatScreen:
	std::cout << tempValg2 << std::endl;

	std::cout << std::endl << "Skriv 1 for at g\x86 tilbage" << std::endl;

	while (true)
	{
		std::cin >> tempValg;

		if (tempValg == "1")
		{
			std::system("cls");
			goto interfaceScreen;
		}

//		std::system("cls");
//		goto modtagRepeatScreen;
	}




historikScreen:

	std::cout << "V\x91lg en operation" << std::endl;
	std::cout << "1. Se hele historikken" << std::endl;
	std::cout << "2. Se seneste besked" << std::endl;
	std::cout << "3. G\x86 tilbage til interface" << std::endl;
	std::cin >> tempValg;

	if (tempValg == "1")
	{
		std::system("cls");
		goto heleHistorikScreen;
	}

	if (tempValg == "2")
	{
		std::system("cls");
		goto latestHistorikScreen;
	}

	if (tempValg == "3")
	{
		std::system("cls");
		goto interfaceScreen;
	}

	std::system("cls");
	goto historikScreen;


heleHistorikScreen:
	std::cout << "Hele historikken for " << user << ":" << std::endl;

	controller.getHeleHistory(user);

	std::cout << std::endl << "Skriv 1 for at g\x86 tilbage" << std::endl;

	while (true)
	{
		std::cin >> tempValg;
		if (tempValg == "1")
		{
			std::system("cls");
			goto historikScreen;
		}
	}


latestHistorikScreen:
	std::cout << "Seneste historik for " << user << ":" << std::endl;

	controller.getSenesteHistory(user);

	std::cout << std::endl << "Skriv 1 for at g\x86 tilbage" << std::endl;

	while (true)
	{
		std::cin >> tempValg;
		if (tempValg == "1")
		{
			std::system("cls");
			goto historikScreen;
		}
	}
}