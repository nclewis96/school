to compile, run 

g++ -std=c++11 -o capDriver driver.cpp frame.cpp frameTable.cpp pageTable.cpp

to run once compiled

./driver programlist.txt programtrace.txt <pageSize> <algorithm> <paging method>

page size is a power of 2 up to 16

algorithm is 
	fifo - first in first out
	
	lru - least recently used
	
	2lru - Second Chance Least Recently Used
	
paging method is 
	p - pre paging 
	
	d - demand paging
	
	
Thanks, sorry this was so late, sucks to suck I guess.