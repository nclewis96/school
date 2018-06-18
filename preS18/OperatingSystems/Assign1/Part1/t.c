int prints(char *s)
{
	//standard in and file buffer
	while(*s){
		 putc(*s++);
	}
	
   return 0;
}

int gets(char s[ ])
{
	//get standard in, give it to s
	char nextChar = getc();
	int i = 0;
	while (nextChar != '\r'){
		s[i] = nextChar;
		nextChar = getc();
		i++;
	}
    return i;
}

main()
{
   char name[64];
   while(1){
     prints("What's your name? ");
     gets(name);
     if (name[0]==0)
        break;
     prints("Welcome "); prints(name); prints("\n\r");
   }
   prints("return to assembly and hang\n\r");
}