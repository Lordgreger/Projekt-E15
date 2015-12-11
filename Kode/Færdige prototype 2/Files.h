#pragma once
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <iostream>


class Files
{
public:
	Files();

	Files(std::string aUsername);
	void AddNewLine(std::string newLine);
	void UpdateVector();
	void ClearText();
	void PrintVector();
	void PrintLatest();
	void PrintLines(int startN, int endM);

	~Files();
protected:
	void FlipVector(std::vector<std::string> aVector);
	std::vector<std::string> HistoryVector;
	std::string Username;

};

