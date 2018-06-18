
#include "pageTable.h"
#include <string>
#include <iostream>
using namespace std;

//Constructor takes pID and mem size
pageTable::pageTable(int procID, int memorySize, int pageOffset ) {
	pID = procID;
	memSize = memorySize;
	pageStart = pageOffset;
}

//Gets the starting page
int pageTable::getPageStart(){
	return pageStart;
}

//Gets the mem size
int pageTable::getMemSize() {
	return memSize;
}

//Gets the Process ID
int pageTable::getPID() {
	return pID;
}

//Gets a page location
int pageTable::getPageLoc(int pageSize, int memLoc) {
	int pgNum = getPageStart();
	pgNum += memLoc / pageSize;
	
	return pgNum;
}

string pageTable::toString(){
	cout << "Process ID " << pID << endl;
	cout << "Memory Size " << memSize << endl;
	cout << "Starting Page " << pageStart << endl;
}

/* int main(){
	pageTable bill(0, 1231, 0);
	bill.toString();
	
} */