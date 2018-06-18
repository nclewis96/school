#ifndef FRAMETABLE_H
#define FRAMETABLE_H
#include <vector>
#include "frame.h"


class frameTable {
	public :
		frameTable();
		int secondChance(std::vector<frame> &frameTable, int position);
		int leastRecentlyUsed(std::vector<frame> frameTable);
		void increaseAge(std::vector<frame> &frameTable, int length);
	private :
		
};

#endif