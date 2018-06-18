#ifndef PAGETABLE_H
#define PAGETABLE_H
#include <string>
using namespace std;

class pageTable {
public :
	pageTable(int pID, int memSize, int pageOffset);
	
	//Gets the starting page
	int getPageStart();

	//Gets the mem size
	int getMemSize();

	//Gets the Process ID
	int getPID();

	//Gets a page location
	int getPageLoc(int pageSize, int memLoc);
	
	string toString();
	
private:
	int pID; 	//Process ID
	int memSize;//Size of process in memory
	int pageStart;//Starting page of the process
	};//end pageTable
	
#endif 