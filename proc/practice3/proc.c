#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s -[a/b]\n",argv[0]);
		return 1;
	}

	if(strcmp(argv[1], "-a") == 0)
	{
		printf("hello ^_^\n");
	}
	else if (strcmp(argv[1], "-b") == 0) 
	{
		printf("hello ^_&\n");
	}
	else
	{
		printf("&_&\n");
	}
	return 0;
}

// int main(int argc, char * argv[])
// {
// 	for(int i = 0;i < argc; i++)
// 	{
// 		printf("argv[%d] -> %s\n",i, argv[i]);
// 	}

// 	return 0;

// }

// int main()
// {
// 	int cnt = 5;
// 	while(cnt)
// 	{
// 		sleep(1);
// 		printf("i am a cmd -> process!\n");
// 		cnt--;
// 	}
// 	return 0;
// }



// int main()
// {
// 	while(1)
// 	{	
// 		fork();
// 		printf("i am a process\n");
// 	}
// 	return 0;
// }
