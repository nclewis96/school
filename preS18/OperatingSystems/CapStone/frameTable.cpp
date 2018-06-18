

#include "frameTable.h"
#include "frame.h"
#include <string>
#include <vector>
#include <iostream>

frameTable::frameTable(){
	
}


//Uses LRU function to find the oldest frame, then flips the bit. 
//If the bit is flipped to 0 from 1, frame gets a second chance
int frameTable::secondChance(std::vector<frame> &frameArray, int position){
	while(frameArray[position].getSecChan() != 0  ){
		//If the frame at the position has been accessed since last 
		//Check, reset it to 0.
		if(frameArray[position].getSecChan() == 1 )
			frameArray[position].flipSecChan(0);
		
		//If the position is beyond the frameArray, restart at 0
		if(position + 1>= frameArray.size()){
			position = 0;
		}else{
			position++;
		}
		
	}
	return position;
}//end Second Chance


//Loops through the frame table and sees which process was the least recently used.
int frameTable::leastRecentlyUsed(std::vector<frame> frameArray){
	int oldestLoc = 0;
	int oldestAge = 0;
	for(int i = 0; i < frameArray.size(); i++){
		if(frameArray[i].getAge() > oldestAge){
			oldestAge = frameArray[i].getAge();
			oldestLoc = i;
		}
	}
	
	return oldestLoc;
}//end leastRecentlyUsed 

//Increases the age of all current frames
void frameTable::increaseAge(std::vector<frame> &frameArray, int length){
	int counter = 0;
	while(counter + 1 <= length){
		if(frameArray[counter].getPID() < 11){
			frameArray[counter].incAge();
		}
		counter++;
	}//end while
}//end increaseAge
