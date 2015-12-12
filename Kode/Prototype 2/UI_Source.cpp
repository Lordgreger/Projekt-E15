#include "C:\Projekt-E15\Projekt-E15\Kode\Prototype 2\Controller.h"


int main()
{
	Controller controller;
	std::string user, pass, tempValg, tempValg2;

firstScreen:
	std::cout << "V\x91lg en operation" << std::endl;		// cout af valgmuligheder
	std::cout << "1. Login" << std::endl;
	std::cout << "2. Opret ny bruger" << std::endl;
	std::cin >> tempValg;

	if (tempValg == "1")									// valg "1" gå til loginScreen
	{
		std::system("cls");									// Reset Konsolvindue
		goto loginScreen;
	}

	if (tempValg == "2")									// valg "2" gå til createUserScreen
	{
		std::system("cls");
		goto createUserScreen;
	}

	std::system("cls");										// forkert valg retur firstScreen
	goto firstScreen;


createUserScreen:
	std::cout << "Username?" << std::endl;					// cin af brugernavn og kodenavn
	std::cin >> user;
	
	std::cin.clear();												//Disse 2 linjer sørger for at ignorere input efter mellemrum
	std::cin.ignore(numeric_limits<streamsize>::max(), '\n');		//Disse 2 linjer sørger for at ignorere input efter mellemrum
		
	std::cout << "Password?" << std::endl;
	std::cin >> pass;

	controller.createUser(user,pass);						// opretter bruger
	
	std::system("pause");
	std::system("cls");										// Reset Konsolvindue
	goto firstScreen;										// retur firstScreen



loginScreen:
	std::cout << "Username?" << std::endl;					// cin af brugernavn og kodenavn
	std::cin >> user;
	std::cout << "Password?" << std::endl;
	std::cin >> pass;

	if (controller.testLogin(user, pass))					// checker om brugernavn og kodeord er korrekt, gå til interfaceScreen
	{
		std::system("cls");
		goto interfaceScreen;
	}

	std::system("cls");
	std::cout << "Forkert login" << std::endl;				// forkert brugernavn eller kodeord, retur til firstScreen
	goto firstScreen;


interfaceScreen:
	std::cout << "V\x91lg en operation" << std::endl;		// cout af valgmuligheder
	std::cout << "1. Send besked" << std::endl;
	std::cout << "2. Modtag besked" << std::endl;
	std::cout << "3. Se historik" << std::endl;
	std::cout << "4. Log ud" << std::endl;
	std::cin >> tempValg;

	if (tempValg == "1")									// valg "1" gå til sendBeskedScreen
	{
		std::system("cls");
		goto sendBeskedScreen;
	}

	if (tempValg == "2")									// valg "2" gå til modtagBeskedScreen
	{
		std::system("cls");
		goto modtagBeskedScreen;
	}

	if (tempValg == "3")									// valg "3" gå til historikScreen
	{
		std::system("cls");
		goto historikScreen;
	}

	if (tempValg == "4")									// valg "4", logout, reset af brugernavn og kodeord, retur firstScreen
	{
		user = "";
		pass = "";
		std::system("cls");
		goto firstScreen;
	}

	std::system("cls");
	goto interfaceScreen;									// forkert valg, retur interfaceScreen


sendBeskedScreen:
	std::cout << "Indtast besked" << std::endl;
	std::cin.ignore();										// stopper aktiv cin
	std::getline(std::cin, tempValg);						// indtast besked 

	std::system("cls");
	std::cout << "Sender besked...";

	controller.sendBesked(tempValg, user);					// sender besked

	std::system("cls");
	goto interfaceScreen;									// retur interfaceScreen


modtagBeskedScreen:
	tempValg2 = "";
	std::cout << "Modtager besked..." << std::endl;
	tempValg2 = controller.modtagBesked(user);				// afventer besked
	std::system("cls");

	std::cout << tempValg2 << std::endl;

	std::cout << std::endl << "Skriv 1 for at g\x86 tilbage" << std::endl;

	while (true)											// while løkke der venter på "1" og går retur til interfaceScreen
	{
		std::cin >> tempValg;

		if (tempValg == "1")
		{
			std::system("cls");
			goto interfaceScreen;
		}
	}


historikScreen:

	std::cout << "V\x91lg en operation" << std::endl;		// cout af valgmuligheder
	std::cout << "1. Se hele historikken" << std::endl;
	std::cout << "2. Se seneste besked" << std::endl;
	std::cout << "3. G\x86 tilbage til interface" << std::endl;
	std::cin >> tempValg;

	if (tempValg == "1")									// valg "1" gå til heleHistorikScreen
	{
		std::system("cls");
		goto heleHistorikScreen;
	}

	if (tempValg == "2")									// valg "2" gå til lastestHistorikScreen
	{
		std::system("cls");
		goto latestHistorikScreen;
	}

	if (tempValg == "3")									// valg "3" gå til interfaceScreen
	{
		std::system("cls");
		goto interfaceScreen;
	}

	std::system("cls");
	goto historikScreen;									// forkert valg retur historikScreen


heleHistorikScreen:
	std::cout << "Hele historikken for " << user << ":" << std::endl;

	controller.getHeleHistory(user);						// udskriver hele historikken

	std::cout << std::endl << "Skriv 1 for at g\x86 tilbage" << std::endl;

	while (true)											// while løkke der venter på "1" og går retur til historikScreen		
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

	controller.getSenesteHistory(user);						// udskriver seneste besked

	std::cout << std::endl << "Skriv 1 for at g\x86 tilbage" << std::endl;

	while (true)											// while løkke der venter på "1" og går retur til historikScreen	
	{
		std::cin >> tempValg;
		if (tempValg == "1")
		{
			std::system("cls");
			goto historikScreen;
		}
	}
}