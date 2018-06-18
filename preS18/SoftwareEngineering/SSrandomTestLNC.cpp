/** **************************************************************
* PROJECT: Service Station
*
* DEVELOPMENT ENVIRONMENTS
* Textwrangler and Notepad++
*
* EXECUTION ENVIRONMENTS
* Katie Server
*
* HISTORY:
* Date		Author			Description
* ====      ======          ===========
* 11/10/16	Nathaniel Lewis	Initial implementation and test
*
* DESCRIPTION:
* Creates 9 random test files that are runnable by the ServiceStationLNC.cpp 
*  file that have between 1 and 9 town configurations with 3-35 towns and 
*  a random number of connections between them.
*****************************************************************/

#include <iostream>
#include <fstream>
#include <time.h>

/** --------------------------------------------------------------
* DESCRIPTION - main
* Creates 9 random test files
* 
* ALGORITHM
* ---------
*
* A01 Initialize int n to track what file we are creating
* A02 Do {
* A03 	Initialize String filename to hold the name of file once it's built
*		Create a new file with name "filename" and open it to be written in
* A04   Initialize int numTownConfig to determine the number of 
			town configurations in the current file
* A05 	For(numTownConfig){
* A06		Initialize numTowns and randomly assign a value between 3 and 35
*			Initialize numConnect and randomly assign a value between 0 and up to 608
				depending on the value of numTowns
*			Write numTowns and numConnect to the current file
* A07		For(numConnect) {
*    			Initialize int townA that chooses a random number 
					between 1 and numTowns
* A08			Do {
*					Initialize int townB that chooses a random num. 
						between 1 and numTowns
*				}While (townA==townB)
* A09 			Write townA and town B to the current file
* 			}//FOR
* A10		Initilize string endline to show the end of a town Config
*			Write endline to the current file
*		}//FOR
*		Close the current file
*		Increment n
*	 }while(n <= 9);
*
* Sample Runs
* -----------
*
* +++++++++++++++++++++++++++++
* +Enter SS.cpp
* +++++++++++++++++++++++++++++
*
* 
* +++++++++++++++++++++++++++++
* +Exit SS.cpp
* +++++++++++++++++++++++++++++
* 
* randTest01.txt
* randTest02.txt
* randTest03.txt
* randTest04.txt
* randTest05.txt
* randTest06.txt
* randTest07.txt
* randTest08.txt
* randTest09.txt
*
*
*CODE CORRECTNESS ARGUMENT
*
* CA01 by L01
* CA02 by L02
* CA03 by L03
* CA04 by L04
* CA05 by L05
* CA06 by L06
* CA07 by L07
* CA08 by L08
* CA09 by L09
* CA10 by L10
*
* */

int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) + n;
}

int main  () {
/*L01*/int n = 1;
srand(time(NULL));
/*L02*/do{
		//String builder that constructs the filename into "randTest0n" where n is 
		//the number of the file.
/*L03*/	std::string filename = "";
			filename = "randTest0";
			std::string endfile = ".txt";
			filename = filename + std::to_string(n) + endfile;
			//open file
			std::ofstream(newFile);
			newFile.open(filename);
			//Randomly selects a number of town configurations from 1 - 9
/*L04*/	int numTownConfig = rand() % 8 + 1;
			//Loops through numTownConfig times
/*L05*/	for(int i = 0; i < numTownConfig; i++){
				//Randomly selects a number of towns from 3 - 35
/*L06*/		int numTowns = rand() % 32 + 3;
				//Randomly selects a number of connections
				int numConnect = rand() % (factorial(numTowns) + 1);
				//writes the numTowns and numConnect to the file
				std::string firstLine = std::to_string(numTowns) + 
						" " + std::to_string(numConnect) + " \n";
				newFile << firstLine;
				//Loops numConnect times to generate the correct 
				//number of connections between towns
/*L07*/		for(int j = 0; j < numConnect; j++){			
					//Randomly selects 2 town numbers between 1 and numTowns
					int townA = rand() % numTowns + 1;
					int townB;
					//Ensures that the two towns chosen are unique.
/*L08*/			do{
						townB = rand() % numTowns + 1;
					}while(townA == townB);		
				// writes the pair to the file, separated by a 
				// space and followed by an end line
/*L09*/			std::string townPair = std::to_string(townA) + 
						" " + std::to_string(townB) + " \n";				
					newFile << townPair;
				}//for (numConnect
				//when all pairs have been written, ends town configuration with 0 0.
/*L10*/		std::string endLine = "0 0 \n";
				newFile << endLine;
				newFile << "\n";
			}//for (townConfig)
		newFile.close();
		n++;
		} while(n <= 9);
	
	
}// main