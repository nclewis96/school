#ifndef _MEMORY
#define _MEMORY

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#define memSize 100
	
	int mymalloc();
	
	int mybfmalloc();
	
	int mywfmalloc();
	
	int mymfree();
	
	int mymdump();

	struct map{
		int m_size;
		int m_addr;
	};
	
	int blockSize[memSize];

	int coreMap[memSize];
	
	#include "mem.c"
	
#endif