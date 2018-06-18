/** **************************************************************
* PROJECT: Mirrors
*
* DEVELOPMENT ENVIRONMENTS
* Notepad++
*
* EXECUTION ENVIRONMENTS
* Katie Server
*
* HISTORY:
* Date		  Author			    Description
* ====      ======          ===========
* 12/12/16	Kodi Neumiller	Initial implementation and Testing
*
* DESCRIPTION:
* Finds the transformation that happened between two given patterns.
*****************************************************************/
//------------
// C++ includes
//------------
#include <iostream>
#include <fstream>
#include <vector>

std::string transformationCheck(char array1[10][10], char array2[10][10], int size) {
				//booleans to keep track of which rotation or reflection happen.
/*L11*/	bool rot90 = true;
				bool rot180 = true;
				bool rot270 = true;
				bool reflection = true;
				bool reflection90 = true;
				bool reflection180 = true;
				bool reflection270 = true;
				bool preservation = true;
				bool improper = true;
				//Loop through each row of the old pattern and check to see if it is in the 
				//correct location on the new pattern.
				//If at any point the loop returns false, the code should not enter the if
				//statement and therefore never set the boolean back to true.
/*L12*/	for (int i = 0; i < size; i++) {
/*L13*/		for (int j = 0; j < size; j++) {
/*L14*/			if (array1[i][j] == array2[i][j] && preservation)
							preservation = true;
						else
							preservation = false;
						if (array1[i][j] == array2[j][size-1-i] && rot90)
							rot90 = true;
						else
							rot90 = false;
						if (array1[i][j] == array2[size-1-i][size-1-j] && rot180)
							rot180 = true;
						else 
							rot180 = false;
						if (array1[i][j] == array2[size-1-j][i] && rot270)
							rot270 = true;
						else 
							rot270 = false;
						if (array1[i][j] == array2[size-1-i][j] && reflection)
							reflection = true;
						else
							reflection = false;
						if (array1[i][j] == array2[j][i] && reflection90)
							reflection90 = true;
						else
							reflection90 = false;
						if (array1[i][j] == array2[i][size-1-j] && reflection180)
							reflection180 = true;
						else
							reflection180 = false;
						if (array1[i][j] == array2[size-1-j][size-1-i] && reflection270)
							reflection270 = true;
						else
							reflection270 = false;
					}
				}
/*L15*/	if (preservation)
/*L16*/		return " was preserved.";
				else if (rot90)
					return " was rotated 90 degrees.";
				else if (rot180)
					return " was rotated 180 degrees.";
				else if (rot270)
					return " was rotated 270 degrees.";
				else if (reflection)
					return " was reflected vertically.";
				else if (reflection90)
					return " was reflected vertically and rotated 90 degrees.";
				else if (reflection180)
					return " was reflected vertically and rotated 180 degrees.";
				else if (reflection270)
					return " was reflected vertically and rotated 270 degrees.";
				else
					return " was improperly transformed.";
				}
int main() {
/*L01*/	int patternID = 1;
				int patternSize;
				//2D arrays that will contain the original and new patterns.
				char patternOrder[10][10];
				char newPattern[10][10];
				std::string fileName;
				//Assign the first number given to be the pattern size.
/*L03*/	while (std::cin >> patternSize) {
					//Loop through each row and add the appropriate values to the arrays
/*L04*/		for (int i = 0; i < patternSize; i++) {
						//Fill the original pattern array
/*L05*/			for (int j = 0; j < patternSize; j++) {
/*L06*/					std::cin >> patternOrder[i][j];
						}
						//Fill the new pattern array
/*L07*/			for (int k = 0; k < patternSize; k++) {
/*L08*/					std::cin >> newPattern[i][k];
						}
					}
/*L09*/		std::cout << "Pattern " << patternID << transformationCheck(patternOrder, newPattern, patternSize);
					std::cout << std::endl;
/*L10*/		patternID++;
					}
}