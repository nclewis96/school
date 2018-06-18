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
* Date		  Author			    Description
* ====      ======          ===========
* 10/18/16	Kodi Neumiller	Initial implementation and Testing
*
* DESCRIPTION:
* Finds the minimal number of services stations needed for the given town configuration
*****************************************************************/
//------------
// C++ includes
//------------
#include <iostream>
#include <fstream>
#include <vector>
/** --------------------------------------------------------------
* DESCRIPTION - main
* Accepts the input and computes the output
* 
* Sample Runs
* -----------
*
* +++++++++++++++++++++++++++++
* +Enter SS.cpp
* +++++++++++++++++++++++++++++
*
* 3 2 1 2 2 3 0 0
* 
* 1
* 
* +++++++++++++++++++++++++++++
* +Exit SS.cpp
* +++++++++++++++++++++++++++++
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
* CA11 by L11
* CA12 by L12
* CA13 by L13
* CA14 by L14
* CA15 by L15
* CA16 by L16
* CA17 by L17
* CA18 by L18
* CA19 by L19
* CA20 by L20
* CA21 by L21
* CA22 by L22
* CA23 by L23
* CA24 by L24
* CA25 by L25
* CA26 by L26
*
****************************************************************/

int main() {
/*L01*/   int numTowns = 0;
						int numPairs = 0;
/*L02*/		std::cin >> numTowns;
						std::cin >> numPairs;
/*L03*/		int townA = 0;
						int townB = 0;
						//Keep track of which towns have a connection
/*L04*/		int serviceMatrix[numTowns + 1][numTowns + 1];
						//set all values in the array = 0
						for(int i =0; i <= numTowns; i++){
							for(int j = 0; j <= numTowns; j++){
								serviceMatrix[i][j] = 0;
							}
						}
						//Populate the array
						for(int i = 0; i < numPairs; i++){
							std::cin >> townA >> townB;
							if(townA == townB){
								serviceMatrix[townA][townB] = 0;
							}else {
								serviceMatrix[townA][townB] = 1;
								serviceMatrix[townB][townA] = 1;
							}//ifelse
						}//for
						//Keep track of which towns have access to a service station		
/*L05*/		bool serviced[numTowns + 1];
						for(int i = 0; i <= numTowns; i++)
	        	serviced[i] = false;		
						int serviceStationCount = 0;
						//Loop through each town in the file and see what it is connected to
/*L06*/		while (true){
/*L07*/		int numLeft = 0;
	        	//If all of the towns are serviced, break out of the loop
/*L08*/		for(int i = 1; i <= numTowns; i++){
/*L09*/			if(serviced[i] == 0){
/*L10*/				numLeft++;
			        }//if
		        }//for
/*L11*/		if (numLeft == 0) {
			        break;
		        }//if 
						//Variable to keep track of what town currently has the greatest number of connections
/*L12*/		int townNumber = 0;
						//Variable to keep track of the number of connections the town has
/*L12*/		int mostConnections = 0;
/*L12*/		int counter = 0;
						//Increment a town's number of connections by 1 
						// everytime it is seen in the loop
/*L13*/		for (int i = 1; i <= numTowns; i++){
/*L14*/		if (serviced[i] == 0){
/*L15*/			for (int j = 1; j <= numTowns; j++){
/*L16*/				counter += serviceMatrix[i][j];
/*L17*/				if (counter >= mostConnections){
/*L18*/					townNumber = i;
/*L19*/					mostConnections = counter;
		    			}//if
			    	}//for
/*L20*/		counter = 0;
							}//if
						}//for
						//Set all towns connected to townNumber which holds the service station to true.
						//Multiple towns may share the greatest number of connections, the town (or row) 
						// that will contain the station will be the town seen first in the array. 
						//If this town is not connected to the other town with the greatest connections, then it
						// will be caught in the next iteration and service stations will be added accordingly.
/*L21*/		serviced[townNumber] = true;
/*L22*/		for (int i = 1; i <= numTowns; i++ ){
/*L23*/		if (serviceMatrix[townNumber][i] == 1){
/*L24*/			serviced[i] = true;
							}//if
						}//for
/*L25*/		serviceStationCount++;
						}//while
/*L26*/		std::cout << serviceStationCount << "\n";
						}//main
