#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
	int ret = fork();

	while(1)
	{
		printf("i am a process,pid:%d,ppid:%d\n",getppid(),getppid());
		sleep(1);
	}

	return 0;
}


// int main()
// {
// 	int ret = fork();

// 	if(ret > 0)
// 	{
// 		printf("you can see me!!!\n");
// 	}
// 	else
// 	{
// 		printf("oops! you can see me!!!!\n");
// 	}
// 	sleep(1);
// 	return 0;
// }


// int main()
// {
// 	while(1)
// 	{
// 		printf("hello lrf! :pid:%d\n",getpid());
// 		sleep(1);
// 	}
// 	return 0;
// }
