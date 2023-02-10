#include <stdio.h>
#include <stdlib.h>

#define EXIT 0

int factorial(int,int);

int main(int argc, char * argv[])
{
	if (argc < 2) return EXIT;

	int input =  atoi(argv[1]);
	printf("Num: %d Fact: %d\n",input,factorial(input,1));	
	return EXIT;
}

int factorial(int numIn, int sum)
{
	if (numIn == 0) return sum;

	sum *= numIn;
	return factorial(--numIn,sum);
}



