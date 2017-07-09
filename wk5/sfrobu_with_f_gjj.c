/* Guo Jiayu
 304-773-262
 cs 35 lab 6
 2/16/17
 */



/*
 sfrobu.c: the objective is to rewrite sfrob.c so that library calls will not be necessary; also, added -f feature as required
 copy's okay
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>

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
    /*
    }
        {
        
        for(;a != 0&&b !=0;a++, b++)
        {
            
            if(*a == ' '&&*b == ' ')
                return 0;
            else if(*b==' '||(*a^42)>(*b^42))
                return 1;
            else if(*a==' '||(*a^42)<(*b^42))
                return -1;
            
        }
        return 0;
    
    
    }
    */
    /*to satisfy (troll) the mighty complier*/
    
}



int frobcmp_f(const char* a, const char* b)
{
    
    for(;a != 0&&b !=0;a++, b++)
    {
        
        if(*a == ' '&&*b == ' ')  /*loop until spaces are reached in both string*/
            return 0;
        else if(*b==' '||(toupper(*a^42))>(toupper(*b^42)))
            return 1;
        else if(*a==' '||(toupper(*a^42))<(toupper(*b^42)))
            return -1;
        
    }
    return 0; /*exact same string*/
       /*to satisfy (troll) the mighty complier*/
    
}

int compare(const void* a, const void* b)  /*a cmp function designed for the demand of qsort*/
{
    
        return frobcmp(*(const char**)a, *(const char**)b);
}


int compare_f(const void* a, const void* b)  /*a cmp function designed for the demand of qsort*/
{
    
    return frobcmp_f(*(const char**)a, *(const char**)b);
}

int main(int argc, char** argv)
{
    int flagged = 0;
    if(argc >2)
    {
        fprintf(stderr, "What's wrong with you??Please don't give any arguments other than flag -f!!!!!!!!");
        exit(1);
    }
    else if(argc == 2)
    {
        if(argv[1][0] == '-' && argv[1][1] == 'f')
            flagged = 1;
        else
        {
            fprintf(stderr, "Cannot recoginze the pattern of this flag/argument. Please treat this program seriously!!");
        }
    }
    
    /*
    if(flagged)
    {
        printf("shiet!!!!");
        exit(0);
    }
    */
    
    struct stat buffer;
    fstat(0, &buffer);
    int size = buffer.st_size + 1;
    
    if(size == 0)
        size += 1024;
    
	int num = 0;
	int i;
	char* array = (char*) malloc(sizeof(char) * size);
    
    
    /*check memory alloc*/
    if(array == 0)
    {
        fprintf(stderr, "Believe it or not, cannot alloc memory");
        exit(1);
    }
    
    
    int myCharInt;
    int fileEnd = read(0, &myCharInt, 1);
    char myChar = (char)myCharInt;
    
    checkFileReadErr();
    
	while(fileEnd > 0)
	{
		array[num] = myChar;
		num++;
		if(num >= size)
		{
			array = (char*)realloc(array, size*2*sizeof(char));
			size *= 2;
		}
		/*myChar = getchar();*/
        
        
        fileEnd = read(0, &myCharInt,1);
        
        if(fileEnd>0)
            myChar = (char)myCharInt;
        
        if(array == 0)
        {
            fprintf(stderr, "Believe it or not, cannot alloc memory");
            exit(1);
        }
        
        checkFileReadErr();
		/*at the end don't forget to read char*/
	}
	/*parse the char array to word array
 * 	to add a space after the last word*/
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
        fprintf(stderr, "Believe it or not, cannot alloc memory");
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

    /*just as it named*/
    if(flagged)
        qsort(word_array, num_words, sizeof(char*), compare_f);
    else
        qsort(word_array, num_words, sizeof(char*), compare);

    
	int p;
    
    /*print everything*/
    char space = ' ';
    int intSP = (int)space;
    
	for(j=0; j<num_words; j++)
	{
    	for(p=0; word_array[j][p]!=' '; p++)
    	{
            int tmp = (int)(word_array[j][p]);
      		write(1, &tmp, 1);
    	}
        write(1, &intSP, 1);
  	}

  	free(array);
  	free(word_array);
  	return 0;

}
