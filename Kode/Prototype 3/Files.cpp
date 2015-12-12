#include "Files.h"


Files::Files()
{
}

Files::Files(std::string aUsername)							//This creates a new text document with given username
{
	Username = aUsername + ".txt";							//.txt is appended to username for quality of life
	UpdateVector();											//Updates the HistoryVector with any existing lines in usernames .txt document
}

void Files::AddNewLine(std::string newLine)					//This is meant for writing new lines into a document
{
	std::ofstream WriteObject(Username, std::ios::app);		//Opens datawriting to usernames .txt document (will make a .txt if none is present)
	WriteObject << newLine + "\n";							//Writes line to .txt document
	WriteObject.close();									//Closes datawriting to .txt (good practice)
}

void Files::UpdateVector()									//This is meant for updating the dataholder for the history
{
	std::string tempString = "";							//Define empty string for temporary dataholding
	HistoryVector = {};										//Clear HistoryVector to avoid writing after old contents

	std::ifstream ReadObject(Username);						//Opens datareading from usernames .txt document
	while (getline(ReadObject, tempString))					//If there is still lines remaining in the document
	{
		HistoryVector.push_back(tempString);				//Add line to vector
	}

	FlipVector(HistoryVector);								//Flip vector to read latest line as index 0
}

void Files::ClearText()										//This is meant for resetting the history of the document
{
	std::ofstream WriteObject(Username);					//Opens datawriting to usernames .txt document
	WriteObject << "";										//Writes line to .txt document (This deletes everything)
	WriteObject.close();									//Closes datawriting to .txt (good practice)
}

void Files::PrintVector()									//Prints entire HistoryVector 
{
	int n = 0;
	int m = HistoryVector.size();							//Gets the length of HistoryVector (Note, if the size of the vector is 5, the index goes from 0 > 4 etc.)
	
	while (n < m)											//Rather simple while loop
	{
		std::cout << HistoryVector[n] << std::endl;
		n++;
	}
}

void Files::PrintLatest()									//Prints latest line
{
	std::cout << HistoryVector[0] << std::endl;				//Achieved simply due to having a flipped HistoryVector
}

void Files::PrintLines(int startN, int endM)				//Prints lines n to m
{
	int n = startN;
	int m = endM;

	while (n <= m)											//n and m refers to index values, means we have to use n <= m
	{
		std::cout << HistoryVector[n] << std::endl;
		n++;
	}
}

void Files::FlipVector(std::vector<std::string> aVector)	//This is meant for reversing the order of the dataholder, so that 0 = latest line, 1 = second last line..
{
	std::vector<std::string> tempVector = aVector;			//Get History vector through method-call

	std::vector<std::string> reverse(tempVector);			//Reverse the parts of vector
	{
		std::reverse(tempVector.begin(), tempVector.end());	//Write the vector backwards
	}

	HistoryVector = tempVector;								//Reversed vector achieved
}

Files::~Files()
{
}




