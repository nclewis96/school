#include "frame.h"
#include "pageTable.h"
#include "frameTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

int main (int argc, char* argv[]){
	int BUFFER = 512;
	string lru = "lru";
	string fifo = "fifo";
	string secLru = "2lru";
	
	//Checks for the correct number of arguments
	if (argc < 6){
		throw std::invalid_argument( "To use: <programList> <commandList> <pageSize> <algorithm> <d/p>" );
	}
	
	//Assigns command line input to values for easier access.
	string pList   = argv[1];
	string cList   = argv[2];
	int pageSize   = std::atoi(argv[3]);
	string alg     = argv[4];
	string pgMethod= argv[5];
	
	int frameTableSize = BUFFER/pageSize;
	
	//checks to see the paging method requested
	int numToReplace;
	//Checks if demand paging was wanted
	if(pgMethod.compare("d") == 0){
		numToReplace = 1;
	}else if(pgMethod.compare("p") == 0){
		numToReplace = 2;
	}else{
		throw std::invalid_argument("Please choose a valid paging method: p/d");
	}
	
	
	std::vector<pageTable> pgTable;
	
	//Reads in all programs and adds them to the pageTable
	std::ifstream pListFile(pList);
	int pID, memSize, pageOffset, counter;
	pListFile >> pID;
	pListFile >> memSize;
	while(!pListFile.eof()){
		
		//If there is more than process, add their starting page and number of pages to find the next process' offset
		if(counter > 0){
			pageOffset = pgTable[counter -1].getPageStart() + (pgTable[counter - 1].getMemSize() / pageSize );
			//If it is not an even page count, add one to the offset
			if(pgTable[counter -1].getMemSize() % pageSize != 0)
				pageOffset++;
		}else {
			pageOffset = 0;
		}
		
		//Add the newest process to the page table. 
		pgTable.emplace_back(pageTable(pID, memSize, pageOffset));
		pListFile >> pID;
		pListFile >> memSize;
		counter++;
	}//end while
	pListFile.close();
	counter = 0;
	
	unsigned long pageFaults = 0;
	try{
		//Reads in command list, and adds pages to the buffer.
		std::vector<frame> frameArray;
		std::ifstream cListFile(cList);
		int pageNum, nullLoc, memLoc, tableLoc;
		int count = 0;
		bool inTable = false;
		frameTable* frameTableObject = new frameTable();
		cListFile >> pID;
		cListFile >> memLoc;
		frame newFrame(pID, pageNum);
		while(!cListFile.eof()){
			
			pageNum = pgTable[pID].getPageLoc(pageSize, memLoc); 
			newFrame = frame(pID, pageNum);
			//Check to see if the page is already in the frameArray.
			for(int i = 0; i < counter; i++){
				if(frameArray[i].getPgNum() == pageNum){
					tableLoc = i;
					inTable = true;
					
					//If the frame is in the table, and we are using 2nd Chance LRU, set bit to 1
					if(alg.compare(secLru) == 0){
						frameArray[tableLoc].flipSecChan(1);
					} else if( alg.compare(lru) == 0){
						frameArray[tableLoc].resetAge();
					}//end if
				}//end if
				
				//If there is a location that is "empty"
				if(frameArray[i].getPID() > 10){
						nullLoc = i;
				}
			}//end for
			
			//If using LRU algorithm, increase the age.
			if(alg.compare(lru) == 0 ){
					frameTableObject->increaseAge(frameArray, counter);
			}	
			
			if(!inTable){
				
				pageFaults++;
				
				//If the frameArray has free spots, put the frame there
				//If the frame is has spots that have yet to be allocated add to the end
				if(counter < frameTableSize){
					frameArray.emplace_back(newFrame);
					counter++;
				//If there are any null locations, add to that location
				}else if(nullLoc < frameTableSize){
					frameArray[nullLoc] = newFrame;
				}else{
					for(int i = 0; i < numToReplace; i++){
						//Use the specified algorithm
						if(alg.compare(lru) == 0){
							//Least Recently Used : Replaces the page that was accessed furthest back in memory
							
							count = frameTableObject->leastRecentlyUsed(frameArray);
							frameArray[count] = newFrame;
						}//end lru if
							
						//First in First Out : Replaces the oldest page in the frame table
						else if (alg.compare(fifo) == 0){
							//Replace the oldest page in the frame table.
							frameArray[count] = newFrame;
							
							//increment count to track the first entry to the frame table, reset after the end.
							if (count + 1 >= frameTableSize){
								count = 0;
							}else {
								count++;
							}
						}//end fifo if
							
						//2nd Chance Least Recently Used : Replaces the a page that has not been accessed since it's last consideration
						else if (alg.compare(secLru) == 0){
							count = frameTableObject->secondChance(frameArray, count);
							frameArray[count] = newFrame;
						}//end Second Chance LRU 
							
							//If the algorithm given is not of the correct name, explain the options and stop the program.
						else{
							throw std::invalid_argument("Please input a valid algorithm: lru fifo 2lru ");
							
						}
						//If prepaging is chosen, find the next frame to add
						if(numToReplace > 1){
							int newPage = newFrame.getPgNum() + 1;
							int maxPage;
							int index = newFrame.getPID();
							
							//Checks to see if the pID plus one would be oustide the scope of the array
							if(newFrame.getPID() + 1 != pgTable.size()){
								maxPage = pgTable[index + 1].getPageStart();
							} else {
								maxPage = pgTable[index].getPageStart() + pgTable[index].getPageLoc(pageSize, pgTable[index].getMemSize());
							}
							if(alg.compare(secLru)== 0)
								count++;
							//If the new page is outside of the current process, then insert a blank page
							if(newPage > maxPage){
								newFrame = frame(11, 0);
							}//endif
							else {
								newFrame = frame(newFrame.getPID(), newPage );
							}//end else
								
						}//endif 
					
					}//endfor
				}//end else
			}//end if
			inTable = false;
			nullLoc = frameTableSize + 1;
			cListFile >> pID;
			cListFile >> memLoc;
								

		}//end while
	//clean up the file and the frameTableObject	
	delete frameTableObject;
	cListFile.close();
	}//end try
	catch(const std::invalid_argument& e){
		std::cerr << "Wrong file name " << e.what() << std::endl;
	}//end catch
	
	//Print the total page faults encountered
	std::cout << "Total Page faults = " << pageFaults << endl;
}//end main