#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		fprintf(stderr, "Please put in 2 arguments!!!");
		exit(1);
	}
	
	int l1 = 0;
	int l2 = 0;
	int i =0, j=0;

	while(argv[1][i] != '\0')
	{l1++; i++;}

	while(argv[1][j] != '\0')
	{l2++; j++;}

	if(l1 != l2)
	{
		fprintf(stderr, "Please put the strings with same length!!!");
		exit(1);
	}

	//check duplicate
	
	for(i = 0; i<l1; i++)
	{
		for(j = i+1; j<l1; j++)
			
		{
			if(argv[1][i] == argv[1][j])
			{
				fprintf(stderr, "Do not put duplicate chars in the first string!!!!!!!");
				exit(1);
			}
		}
	} 
	
	char rbuf[20], wbuf[20];
	char myChar;
	int found = 0;
	while(read(0,rbuf,1))
	{
		myChar = rbuf[0];
		found = 0;
		for(i=0; i<l1; i++)
		{
			if(myChar == argv[1][i])
			{
				found = 1;
				wbuf[0] = argv[2][i];
			}
		}
		if(!found)
			wbuf[0] = rbuf[0];
		write(1, wbuf, 1);
	}
}
