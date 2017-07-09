/*
 Guo, Jiayu
 304-773-262
 cs35l*/

/* sfrob.c: to (lexicographically) sort a certain type of encoded file without actually 'decoding' it*/
/*copy's OKay*/
/*******************************************************/


#include <stdio.h>
#include <stdlib.h>

/*check if failed to read files*/
void checkFileReadErr()
{
    if(ferror(stdin))
    {
        fprintf(stderr, "Error while reading file!");
        exit(1);
    }
}


int frobcmp(const char* a, const char* b)
{
	for(;a != 0&&b !=0;a++, b++)
	{

		if(*a == ' '&&*b == ' ')  /*loop until spaces are reached in both string*/
			return 0;
		else if(*b==' '||(*a^42)>(*b^42))
			return 1;
		else if(*a==' '||(*a^42)<(*b^42))
			return -1;

	}
	return 0; /*exact same string*/
}

int compare(const void* a, const void* b)  /*a cmp function designed for the (endless) demand of qsort*/
{
	return frobcmp(*(const char**)a, *(const char**)b); /*cast a to pointer of "cstring", and * it to be passed into frobcmp*/
}

int main()
{
	/* printf("%d", frobcmp ("a","a"));
	 return 0;*/
	int size = 64;
	int num = 0;
	int i;
	char* array = (char*) malloc(sizeof(char) * size);
    
    
    /*check memory alloc*/
    if(array == 0)
    {
        fprintf(stderr, "Cannot alloc memory!!!");
        exit(1);
    }

	char myChar = getchar();
    
    checkFileReadErr();
    
	while(myChar != EOF)
	{
		array[num] = myChar;
		num++;
		if(num >= size)
		{
			array = (char*)realloc(array, size*2*sizeof(char));
			size *= 2;
		}
		myChar = getchar();
        
        checkFileReadErr();
		/*at the end don't forget read char*/
	}
	/*parse the char array to word array
	to add a space after the last word*/
	if(array[num-1] != ' ')
	{
		array[num] = ' ';
		num ++;
	}
	int num_words = 0;
	/*count the number of words*/
	for (i = 0; i <= num -1; i++)
    {	
    	if (array[i] == ' ')
    		num_words++;
   	}
   	



	
   	char** word_array = (char**)malloc(num_words*sizeof(char*));
    
    /*check memory alloc*/
    if(word_array == 0)
    {
        fprintf(stderr, "Cannot alloc memory!!!");
        exit(1);
    }
    
    int j;
  	int counter = 0;
    int q;
    
    /*to classify a string into words*/
    
    int bs=0;
    
    word_array[bs]=array;
    for (j = 0; j<num; j++){
        if(array[j]==' '){
            bs++;
        if(j<(num-1))
            word_array[bs]=&array[j+1];
        }
    }
/*
   	for (i = 0; i<num; i++)
   	{
        q = 0;
        while(array[i] != ' ')
        {
            word_array[counter][q] = array[i];
            i++;
            q++;
        }
        counter++;
	}
 */
/*
	int writeArray_index = 0;
  	for (i = 0; i < num; i++)
  	{
    word_array[writeArray_index++] = &array[i];
    while (array[i] != ' ') { i++; }
  	}

*/
    
    /*just as it named*/
    
	qsort(word_array, num_words, sizeof(char*), compare);
    
    
	int p;
    
    /*print everything*/
    
	for(j=0; j<num_words; j++)
	{
    	for(p=0; word_array[j][p]!=' '; p++)
    	{
      		putchar(word_array[j][p]);
    	}
    	putchar(' ');
  	}

  	free(array);
  	free(word_array);
  	return 0;

}