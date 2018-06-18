#include <iostream>
#include <fstream>
#include <vector>

int main() {
/* L01 */int numTowns = 0;
		int numPairs = 0;
		std::cin >> numTowns;
		std::cin >> numPairs;
        int townA = 0;
	    int townB = 0;
        //Keep track of which towns have a connection
		int serviceMatrix[numTowns + 1][numTowns + 1];
        //set all values in the array = 0
       	for(int i =0; i <= numTowns; i++){
        	for(int j = 0; j <= numTowns; j++){
        		serviceMatrix[i][j] = 0;
   	    	}//for
       	}//for
       	//Populate the array
        for(int i = 0; i < numPairs; i++){
        	std::cin >> townA >> townB;
	    	serviceMatrix[townA][townB] = 1;
	        serviceMatrix[townB][townA] = 1;
        }//for
	    int nmbrRoads[numTowns + 1];
	    for(int i = 1; i <= numTowns; i++){
	    	for(int j = 0; j <+ numTowns; j++){
	    		if(serviceMatrix[i][j] == 1)
	    			nmbrRoads[i]++;
	    	}//for
	    }//for
	     //Keep track of which towns have access to a service station		
		std::string serviced[numTowns + 1];
        for(int i = 1; i <= numTowns; i++)
	        serviced[i] = "N";
	    int townNums[1 + numTowns];
	    for(int i = 1; i <=numTowns; i++)
	    	townNums[i] = i;
	    int townNumsPermuted[1 + numTowns];
        int minServStations;
        for(int i = 0; i <= numTowns; i++)
        	townNumsPermuted[i] = townNums[i];
        
/* L02 */while(true){
/* L03 */   int numSSPerm = 0;
			for(int i = 1; i <= numTowns; i++)
	       		serviced[i] = "N";
/* L04 */   for(int i = 1; i <= numTowns; i++){
/* L05 */       int townX = townNumsPermuted[i];
/* L06 */    	if(serviced[townX].compare("AT") != 0 || serviced[townX].compare("SS") != 0 ){
					for(int j = 1; j <= numTowns; j++){
						if(serviceMatrix[i][j] == 1 && serviced[j].compare("SS") == 0)
/* L07 */					serviced[townX] = "AT";
					}//for
				}//if
/* L08 */		else {
/* L09 */			numSSPerm++;
					serviced[townX] = "SS";
				}//else	
/* L10 */   }//for
			//Check if the num Service Stations this permutation is less than the current
			//minimum
/* L11 */   if(numSSPerm < minServStations){
				minServStations = numSSPerm;
			}//if
/* L12 */   for(int i = 1; i <= numTowns; i++){
				if(townNumsPermuted[i] + 1 > numTowns){
					townNumsPermuted[i] = 1;
				}//if
				else {
					townNumsPermuted[i] = townNumsPermuted[i] + 1;
				}//else
			}//for
			bool allPermutations = false;
			for(int i = 1; i <= numTowns; i++){
/* L13 */		if(townNumsPermuted[i] == townNums[i]){	
/* L14 */			allPermutations = true;
        		}//if
        		else{
        			allPermutations = false;
        		}//else
        	}//for
        	if(allPermutations)
        		break;
    	}//while
    	std::cout << minServStations << "\n";
}