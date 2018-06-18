#include "frame.h"
#include <string>
#include <iostream>
using namespace std;

frame::frame(int procID, int pgNum){
	pID = procID;
	pageNum = pgNum;
	age = 0;
	secChance = 0;
}

//Copy Constructor 
frame::frame(const frame& newFrame ){
	pID = newFrame.getPID();
	pageNum = newFrame.getPgNum();
	age = newFrame.getAge();
	secChance = newFrame.getSecChan();
}

int frame::getPID() const{
	return pID;
}

int frame::getPgNum() const{
	return pageNum;
}
		
int frame::getSecChan() const{
	return secChance;
}
		
int frame::getAge() const{
	return age;
}

void frame::incAge(){
	age = age + 1;
}

void frame::flipSecChan(int bit){
	secChance = bit;
}

void frame::resetAge(){
	age = 0;
}

string frame::toString(){
	cout << "Process ID " << pID << endl;
	cout << "Page Number "<< pageNum << endl;
	cout << "Second Chance Bit " << secChance << endl;
	cout << "Age of page " << age << endl;
	
}

frame& frame::operator=(const frame& rhs){
	pID = rhs.getPID();
	pageNum = rhs.getPgNum();
	secChance = rhs.getSecChan();
	age = rhs.getAge();
	
}
 
/*int main(){
	frame bob (0, 122);
	bob.toString();
	
	
	
} */