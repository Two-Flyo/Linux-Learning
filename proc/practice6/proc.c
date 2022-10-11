#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	if(fork() == 0)
	{
		//child
		//exec*
		exit(1);
	}
	//parent
	waitpid(-1, NULL, 0);
	printf("wait success!\n");
	
	return 0;
}

//int main()
//{
//	pid_t id = fork();
//	if(id == 0)
//	{
//		printf("i am a process! pid: %d\n",getpid());
//		sleep(5);
//		execl("/usr/bin/ls", "ls", "-l" , NULL);
//		printf("hello world!\n");
//		printf("hello world!\n");
//		printf("hello world!\n");
//		printf("hello world!\n");
//		printf("hello world!\n");
//		printf("hello world!\n");
//		exit(0);
//	}
//	while(1)
//	{
//		printf("i am a father!\n");
//		sleep(1);
//	}
//
//	return 0;
//}

// int main()
// {
// 	printf(" i am a process!,pid:%d \n",getpid());
// 	execl("/usr/bin/ls", "ls", "-a"," -l", NULL);//执行程序替换

// 	printf("hello world!\n");
// 	printf("hello world!\n");
// 	printf("hello world!\n");
// 	printf("hello world!\n");
// 	printf("hello world!\n");
// 	printf("hello world!\n");
// 	printf("hello world!\n");
// 	return 0;
// }
