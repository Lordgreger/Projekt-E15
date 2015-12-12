#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class Login
{
public:
	Login();
	~Login();
	bool testLogin(std::string uName, std::string pWord); //Funktion der tester login via validateLogin
	void addUser(std::string uName, std::string pWord); //Funktion der tilføjer bruger

protected:
	bool validateLogin(std::string useName, std::string pasWord); //Funktion der validerer et login
	bool testUser(std::string useName);
};

