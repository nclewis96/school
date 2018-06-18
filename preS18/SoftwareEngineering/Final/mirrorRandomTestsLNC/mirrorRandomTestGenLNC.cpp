/** ******************************************************
* PROJECT: Mirror, Mirror for ESOF322
*
* FILE: mirrorRandomTestGenLNC.cpp
*
* DEV ENVIRONMENTS: TestWrangler on macOS
*
* EXECUTION ENVIRONMENTS: Linux command line
*
* HISTORY:
* Date		Author				Description
* ====		======				===========
* 12/13/16  Nathaniel Lewis	 	    Initial implementation and test
*
* DESCRIPTION:
* Creates random test cases to be used for MirrorRAR.cpp. 
* Conforms to the MTM Standard for C++ Source Fles.
********************************************************/

//-------------
// C++ includes
//--------------
#include <stdio.h>      
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <cstdio>

//---------------
// C++ statements
//---------------
using namespace std;

/** -------------------------------------------
* DESCRIPTION - main
* Program generates 20 random test cases each
* containing 5 to 15 cases for MirrorAMD.cpp
*
* REQUIREMENTS
* ------------
* R01 Generate 20 different input files.
* R02 Each input file generated must contain 5 to 10 patterns.
* R03 The output in each file will one of the transformations defined by Mirror, 
*	  Mirror.
* R04 Each test case needs to be purely random.
*
* DESIGN
* 
* Significant variables
* ---------------------
* int caseNmbr			//The number of patterns in the current input file to create
* int patternSize			//The randomly generated dimension size of the current 
*						//pattern set
* origPatt[][]			//Randomly generated first pattern
* modPatt[][]			//Randomly generated modified pattern
* int rndmTransform		//A randomly generated integer that determines the 
*						//transformation being performed on the current set of 
*						//patterns
* 
*
* Solution analysis
* -----------------
* To create randomly generated tests, a random pattern is first be created. 
* A random pattern is created by assigning each position in a 2D array 
* representation of the pattern to a "X" or a "." A random integer is then 
* created between 0 and 8. A specific transformation is then performed on 
* the pattern to create the modified pattern. Then it is written to a file to test.
*
* ALGORITHM
* ---------
* A01		For (every number of ouput files desired) {
*				Open a new file, smtst_X_in
* A02			Set caseNmbr to a Random integer between 5 and 15.
* A03			For (every number of random cases, caseNmbr){			
* 					Initialize int patternSize, char origPatt[][], char modPatt[][]
* 					For (every row in patternSize){
*						For (every column in patternSize){
* A04						Set modPatt[row][col] and origPatt[row][col] to "X", or 
*							to ".", randomly.
*						}/For
*					}//For
* A05				Set random int rndmTransform to int in [0, 8]
* A06				If (rndmTransform < 1){ 
*						Make 90 degree rotation 
*					}//If
* A07				Else if (rndmTransform < 2){ 
*						Make 180 degree rotation
*					}//Else if
* A08				Else if (rndmTransform < 3){ 
*						Make 270 degree rotation
*					}//Else if
* A09				Else if (rndmTransform < 4){ 
*						Make reflection
*					}//Else if
* A10				Else if (rndmTransform < 5){ 
*						Make reflection followed by 90 degree rotation
*					}//Else if
* A11				Else if (rndmTransform < 6){ 
*						Make reflection followed by 180 degree rotation
*					}//Else if
* A12				Else if (rndmTransform < 7){ 
*						Make reflection followed by 270 degree rotation
*					}//Else if
* A13				Else if (rndmTransform < 8){ 
*						Make random improper transformation
*					}//Else if
* A14				Else { 
*						Make preservation (copy of origPatt) 
*					}//Else
*				}//For
*			}//For
*
*
* ALGORITHM CORRECTNESS ARGUMENT
* 	R01 by A01.
*	R02 by A02.
*	R03 by A07-A14.
*	R04 by A05.
*-------------------------------------------------*/

int main(){
	srand(time(NULL));
	
	int testNmbr = 20;
	
	for(int indx = 1; indx <= testNmbr; indx++){
		//Open file & overwrite onto it (creates a file if non existant).
		ofstream file;
		char filename[20];
		snprintf(filename, sizeof(filename), "mirrorLNCT%d.txt", indx);
		file.open(filename);
		file < "";
		int caseNmbr = rand()%15 + 5;
		for(int caseIndx = 0; caseIndx < caseNmbr; caseIndx++){
			int patternSize = rand()%10 + 1;
			char origPatt[patternSize][patternSize];
			char modPatt[patternSize][patternSize];
			for(int rowIndx = 0; rowIndx < patternSize; rowIndx++){
				for(int colmnIndx = 0; colmnIndx < patternSize; colmnIndx++){
					int rndmShad = rand()%2;
					if(rndmShad < 1){
						modPatt[rowIndx][colmnIndx] = 'X';
						origPatt[rowIndx][colmnIndx] = 'X';
					}//if
					else{
						origPatt[rowIndx][colmnIndx] = '.';
						modPatt[rowIndx][colmnIndx] = '.';
					}//else
				}//for
			}//for
			int rndmTransform = rand()%9;
			if(rndmTransform < 1){
				for(int vertIndx = 0; vertIndx < patternSize; vertIndx++){
					for(int horixIndx = 0; horixIndx < patternSize; horixIndx++){
						modPatt[vertIndx][horixIndx] = 
								origPatt[patternSize-horixIndx-1][vertIndx];
					}//for
				}//for
			}//if - 90 degrees
			else if(rndmTransform < 2){
				for(int vertIndx = 0; vertIndx < patternSize; vertIndx++){
					for(int horixIndx = 0; horixIndx < patternSize; horixIndx++){
						modPatt[vertIndx][horixIndx] = 
								origPatt[patternSize-vertIndx-1][patternSize-horixIndx-1];
					}//for
				}//for
			}//else if - 180 degrees
			else if(rndmTransform < 3){
				for(int vertIndx = 0; vertIndx < patternSize; vertIndx++){
					for(int horixIndx = 0; horixIndx < patternSize; horixIndx++){
						modPatt[vertIndx][horixIndx] = 
								origPatt[horixIndx][patternSize-vertIndx-1];
					}//for
				}//for
			}//else if - 270 degrees
			else if(rndmTransform < 4){
				for(int vertIndx = 0; vertIndx < patternSize; vertIndx++){
					for(int horixIndx = 0; horixIndx < patternSize; horixIndx++){
						modPatt[vertIndx][horixIndx] = 
								origPatt[patternSize-vertIndx-1][horixIndx];
					}//for
				}//for
			}//else if - vertical reflection 
			else if(rndmTransform < 5){
				int vertIndx = 0;
				while (vertIndx < patternSize){
					for(int horixIndx = 0; horixIndx < patternSize; horixIndx++){
						modPatt[vertIndx][horixIndx] = 
								origPatt[horixIndx][vertIndx];
					}//for
					vertIndx++;
				}//while
			}//else if - vertical reflection and 90 degrees
			else if(rndmTransform < 6){
				int vertIndx = 0;
				while (vertIndx < patternSize){
					for(int horixIndx = 0; horixIndx < patternSize; horixIndx++){
						modPatt[vertIndx][horixIndx] = 
								origPatt[vertIndx][patternSize-horixIndx-1];
					}//for
					vertIndx++;
				}//while
			}//else if - vertical reflection and 180 degrees
			
			else if(rndmTransform < 7){
				int vertIndx = 0;
				while (vertIndx < patternSize){
					for(int horixIndx = 0; horixIndx < patternSize; horixIndx++){
						modPatt[vertIndx][horixIndx] = 
								origPatt[patternSize-horixIndx-1][patternSize-vertIndx-1];
					}//for
					vertIndx++;
				}//while
			}//else if - vertical reflection and 270 degrees
			else if(rndmTransform < 8){
				for(int rowIndx = 0; rowIndx < patternSize; rowIndx++){
					for(int colmnIndx = 0; colmnIndx < patternSize; colmnIndx++){
						int rndmShad = rand()%2;
						if(rndmShad < 1){
							modPatt[rowIndx][colmnIndx] = 'X';
						}//if
						else{
							modPatt[rowIndx][colmnIndx] = 'X';
						}//else
					}//for
				}//for
			}//else if - improper transformation
			file << patternSize << endl;
			for(int rowIndx = 0; rowIndx < patternSize; rowIndx++){
				for(int colmnIndx = 0; colmnIndx < patternSize; colmnIndx++){
					file << origPatt[rowIndx][colmnIndx];
				}//for
				file << " ";
				for(int colmnIndx = 0; colmnIndx < patternSize; colmnIndx++){
					file << modPatt[rowIndx][colmnIndx];
				}//for
				file << endl;
			}//for	
		}//for
	}//for
	return 0;
}//main()
//end mirrorRandomTestGenRARcpp