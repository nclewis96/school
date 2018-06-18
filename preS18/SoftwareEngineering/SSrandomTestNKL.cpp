#include <iostream>
#include <fstream>

int sum(int n)
{
  return (n == 1 || n == 0) ? 1 : sum(n - 1) + n;
}

int main  () {
	int n = 1;
	do{
		//String builder that constructs the filename into "randTestN" where N is 
		//the number of the file.
		std::string filename = "";
		filename = "SS_randTestFiles/randTest";
		std::string endfile = ".txt";
		filename = filename + std::to_string(n) + endfile;
		//open file
		std::ofstream(newFile);
		newFile.open(filename);
		//Randomly selects a number of town configurations from 1 - 9
		int numTownConfig = rand() % 8 + 1;
		//Loops through numTownConfig times
		for(int i = 0; i < numTownConfig; i++){
			//Randomly selects a number of towns from 3 - 35
			int numTowns = rand() % 32 + 3;
			//Randomly selects a number of connections
			int numConnect = rand() % (sum(numTowns) + 1);
			//writes the numTowns and numConnect to the file
			std::string firstLine = std::to_string(numTowns) + " " + std::to_string(numConnect) + " \n";
			newFile << firstLine;
			//Loops numConnect times to generate the correct number of connections between towns
			for(int j = 0; j < numConnect; j++){			
				//Randomly selects 2 town numbers between 1 and numTowns
				int townA = rand() % numTowns + 1;
				int townB = rand() % numTowns + 1;		
				// writes the pair to the file, separated by a space and followed by an end line
				std::string townPair = std::to_string(townA) + " " + std::to_string(townB) + " \n";				
				newFile << townPair;
			}//for (numConnect
			//when all pairs have been written, ends town configuration with 0 0.
			std::string endLine = "0 0 \n";
			newFile << endLine;
			newFile << "\n";
		}//for (townConfig)
	newFile.close();
	n++;
	} while(n <= 9);
}// main