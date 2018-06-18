/** **************************************************************
* PROJECT: Mirror
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
* 12/12/16	Nathaniel Lewis	Initial implementation and test
*
* DESCRIPTION:
* Finds the transformation that occurs between pattern 1 and pattern 2 
*****************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
std::string transformationCheck(char array1[10][10], char array2[10][10], int size) {
	//booleans to keep track of which rotation or reflection happen.
/*L11*/	bool rotate90 = true;
		bool rotate180 = true;
		bool rotate270 = true;
		bool reflect = true;
		bool reflect90 = true;
		bool reflect180 = true;
		bool reflect270 = true;
		bool preservation = true;
		bool improper = true;
		//Loop through each row of the old pattern and check to see if it is in the 
		//correct location on the new pattern.
/*L12*/	for (int i = 0; i < size; i++) {
/*L13*/		for (int j = 0; j < size; j++) {
/*L14*/			if (array1[i][j] == array2[i][j] && preservation)
					preservation = true;
				else
					preservation = false;
				if (array1[i][j] == array2[j][size-1-i] && rotate90)
					rotate90 = true;
				else
					rotate90 = false;
				if (array1[i][j] == array2[size-1-i][size-1-j] && rotate180)
					rotate180 = true;
				else 
					rotate180 = false;
				if (array1[i][j] == array2[size-1-j][i] && rotate270)
					rotate270 = true;
				else 
					rotate270 = false;
				if (array1[i][j] == array2[size-1-i][j] && reflect)
					reflect = true;
				else
					reflect = false;
				if (array1[i][j] == array2[j][i] && reflect90)
					reflect90 = true;
				else
					reflect90 = false;
				if (array1[i][j] == array2[i][size-1-j] && reflect180)
					reflect180 = true;
				else
					reflect180 = false;
				if (array1[i][j] == array2[size-1-j][size-1-i] && reflect270)
					reflect270 = true;
				else
					reflect270 = false;
			}//for
		}//for
/*L15*/	if (preservation)
			return " was preserved.";
		else if (rotate90)
			return " was rotated 90 degrees.";
		else if (rotate180)
			return " was rotated 180 degrees.";
		else if (rotate270)
			return " was rotated 270 degrees.";
		else if (reflect)
			return " was reflected vertically.";
		else if (reflect90)
			return " was reflected vertically and rotated 90 degrees.";
		else if (reflect180)
			return " was reflected vertically and rotated 180 degrees.";
		else if (reflect270)
			return " was reflected vertically and rotated 270 degrees.";
/*L16*/	else
			return " was improperly transformed.";
	}//transformCheck()
/** --------------------------------------------------------------
* DESCRIPTION - main
* Accepts the input and calls transformCheck, outputs the result
* 
* Sample Runs
* -----------
*
* +++++++++++++++++++++++++++++
* +Enter mirror.cpp
* +++++++++++++++++++++++++++++
*
* 5
* .x... ..x..
* x..x. .x...
* ..x.x ..x..
* ..... x.x..
* x.... .x..x
*
* Pattern 1 was Rotated 90 Degrees.
* 
* +++++++++++++++++++++++++++++
* +Exit mirror.cpp
* +++++++++++++++++++++++++++++
* 
* */
int main() {
/*L01*/	int patternID = 1;
		int patternSize;
/*L02*/	char patternOrder[10][10];
		char newPattern[10][10];
		//Assign the first number given to be the pattern size.
/*L03*/	while (std::cin >> patternSize) {
			//2D arrays that will contain the original and new patterns.
			//Loop through each row and add the appropriate values to the arrays
/*L04*/		for (int i = 0; i < patternSize; i++) {
				//Fill the original pattern array
/*L05*/			for (int j = 0; j < patternSize; j++) {
/*L06*/				std::cin >> patternOrder[i][j];
				}//for
				//Fill the new pattern array
/*L07*/			for (int k = 0; k < patternSize; k++) {
/*L08*/				std::cin >> newPattern[i][k];
				}//for
			}//for
/*L09*/		std::cout << "Pattern " << patternID << 
				transformationCheck(patternOrder, newPattern, patternSize);
			std::cout << std::endl;
			//Assign the next number given to be the pattern size.
/*L10*/		patternID++;		
		}//while
}