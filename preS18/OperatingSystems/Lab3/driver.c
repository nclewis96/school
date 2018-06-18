#include "mem.c"

int main(){
  //Setup the core map.
  struct map coremap[memSize];
  coremap[0].m_size = memSize;
  coremap[0].m_addr = 0;
  coremap[1].m_size = 0;
  coremap[1].m_size = 0;

  int i =0;
  //Setup my allocation table.
  for(i = 0; i < memSize; i++){
    blockSize[i]=0;
  }
  
  printf("Print empty map\n");
  //Print empty map
  mymdump(coremap);
  
  printf("\nAdd an allocation of one and reprint\n");
  //Try adding one space.
  mybfmalloc(coremap, 1);

  //Print map with change.
  mymdump(coremap);
  
  coremap[1].m_size = 20;
  coremap[0].m_size = coremap[0].m_size -20;
  coremap[1].m_addr = coremap[0].m_size + coremap[0].m_addr;
  coremap[2].m_size = 0;
  coremap[2].m_size = 0;

  printf("\n\nManually changed map. Testing worst fit (Adding size 3) . Before:\n");
  mymdump(coremap);

  mywfmalloc(coremap, 3);

  printf("After worst fit:\n");
  mymdump(coremap);

  printf("\nTest best fit (size 5):\n");
  mybfmalloc(coremap, 5);
  mymdump(coremap);
  
  printf("\nTesting First Fit (size 9):\n");
  mymalloc(coremap, 9);
  mymdump(coremap);

  printf("\nAdding three size 5 allocations.\n");
  //Set up for a freeing test
  mybfmalloc(coremap, 5);
  mybfmalloc(coremap, 5);
  mybfmalloc(coremap, 5);
  printf("Set up for mymfree test:\n");
  mymdump(coremap);
  
  
  printf("Post removing leftmost allocation. (one sided)\n");
  mymfree(coremap, 80);
  mymdump(coremap);

  printf("Post removing middle of three allocated areas:\n");
  mymfree(coremap, 90);
  mymdump(coremap);

  printf("Returning all memory: \n");
  mymfree(coremap, 0);
  mymfree(coremap, 4);
  mymfree(coremap, 85);
  mymfree(coremap, 95);
  mymfree(coremap, 1); 
  mymdump(coremap);

  return 0;
}
