#ifndef FRAME_H
#define FRAME_H
#include <string>
using namespace std;

class frame {
	public : 
		frame(int procID, int pgNum);
		frame(const frame& newFrame);
		int getPID() const;
		int getPgNum() const;
		int getSecChan() const;
		int getAge() const;
		void incAge();
		void flipSecChan(int bit);
		void resetAge();
		string toString();
		frame& operator= (const frame& rhs);
	private :
		int pID;
		int pageNum;
		int secChance; 
		int age;
	
	
};

#endif