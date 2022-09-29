#include <stdio.h>
#include <unistd.h>
int main()
{
	while(1)
	{	
		fork();
		printf("i am a process\n");
	}
	return 0;
}
