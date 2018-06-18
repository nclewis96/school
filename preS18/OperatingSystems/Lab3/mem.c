#include "mem.h"
#ifndef _MEM_ALLOC
#define _MEM_ALLOC


//Memory Allocation using the First Fit Algorithm
//The first block that is larger than the size given is used
int mymalloc(struct map *mp, int size)
{
	register int a;
	register struct map *bp;
	
	for (bp = mp; bp->m_size; bp++){
		if ( bp->m_size >= size ){
			a = bp->m_addr;
			bp->m_addr = bp->m_addr + size;
			if ( (bp->m_size = bp->m_size - size) == 0){
				do {
					bp++;
					(bp-1)->m_addr = bp->m_addr;
				} while( (bp-1)->m_size = bp->m_size);
			}
			blockSize[a] = size;
			return(a);
		}
	}
	return(0);
}

//Memory Allocation using the Best Fit Algorithm
//Smallest block that still fits the given size is used
int mybfmalloc(struct map *mp, int size)
{
	register int a;
	register struct map *bp;
	int bestFit = INT_MAX;
	register struct map *best;
	for(bp = mp; bp->m_size; bp++){
		if( (bp->m_size >= size) && bp->m_size < bestFit){			
			bestFit = bp->m_size;
			best = bp;
		}
	}
		
	if ( bestFit < INT_MAX){
		a = best->m_addr;	
		best->m_addr = best->m_addr + size;
		if ( (best->m_size = best->m_size - size) == 0){
			do {
				best++;
				(best-1) ->m_addr = best->m_addr;
			} while( (best-1)->m_size = best->m_size);
		}	
		blockSize[a] = size;
		return(a);
	}
	
	return(0);
}

//Memory Allocation that uses the Worst Fit Algorithm
//The Largest block is used for the given size.
int mywfmalloc(struct map *mp, int size)
{
	register int a;
	register struct map *bp;
	register struct map *worst;
	int worstFit = 0;
	
	for(bp = mp; bp->m_size; bp++) {
		if( (bp->m_size >= size) && bp->m_size > worstFit){
				worst = bp;
				worstFit = bp->m_size;
		}
	}
		
	
	if ( worstFit >= size && worstFit > 0){
		a = worst->m_addr;
		worst->m_addr = worst->m_addr + size;
		if ( (worst->m_size = worst->m_size - size) == 0){
			do {
				worst++;
				(worst-1) ->m_addr = worst->m_addr;
			} while( (worst-1)->m_size = worst->m_size);	
		}	
		blockSize[a] = size;
		return(a);
	}
		
	return(0);
}

//Frees up memory block starting at aa  
int mymfree(struct map *mp, int aa)
{
	register struct map *bp;
	register int t;
	register int a;
	int size = blockSize[aa];
	blockSize[aa] = 0;
	a = aa;
	for (bp = mp; bp->m_addr<=a && bp->m_size!=0; bp++);
	if (bp>mp && (bp-1)->m_addr+(bp-1)->m_size == a) {
		(bp-1)->m_size = (bp-1)->m_size + size;
		if (a+size == bp->m_addr){
			(bp-1)->m_size = (bp-1)->m_size + bp->m_size;
			while(bp->m_size) {
				bp++;
				(bp-1)->m_addr = bp->m_addr;
				(bp-1)->m_size = bp->m_size;
			}
		}
	} else {
		if (a+size == bp->m_addr && bp->m_size) {
			bp->m_addr = bp->m_addr - size;
			bp->m_size = bp->m_size + size;
		} else if(size){ 
			do{
				t = bp->m_addr;
				bp->m_addr = a;
				a = t;
				t = bp->m_size;
				bp->m_size = size;
				bp++;
			} while(size = t);
		bp->m_size = 0;
		}
	}
}

/*
prints out a free space table pointed to by ptr, one entry per line. 
*/
int mymdump(struct map* ptr){
	int i = 0;
	struct map* el = ptr;
	printf("Entry:\tSize:\tAddress:\n");
	for(el = ptr; el->m_size; el++) {
		printf(" %d\t%d\t%d\n", i, el->m_size, el->m_addr);
		i++;
	}
}

#endif