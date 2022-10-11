#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t id = fork();
	if(id == 0)
	{
		//child
		int cnt = 10;
		while(cnt)
		{
			printf("child[%d] is running: cnt is : %d\n",getpid(),cnt);
			cnt--;
			sleep(1);
		}
		exit(1);
	}
	//parent
	int status = 0;
	while(1)
	{
		pid_t ret = waitpid(id, &status, WNOHANG);
		if(ret == 0)
		{
			//子进程没有退出，但是waitpid等待是成功的，需要父进程重复进行等待
			printf("Do father things!\n");
		}
		else if(ret > 0)
		{
			//子进程退出了，waitpid也成功了，获取到了对应的结果
		 	printf("father process wait:%d, success,status:%d ,status exit signal:%d \n",ret,(status>>8)&0xFF,status&0xFF);
			break;
		}
		else
		{
			perror("waitpid:");
			break;
		}
		sleep(1);
	}

	//int status = 0;
	//sleep(5);
	//printf("father wait begin!\n");
	//pid_t ret = waitpid(id,&status,0);
	//if(ret > 0)
	//{
	//	if(WIFSIGNALED(status)) //没有收到任何退出信号的
	//	{
	//		//进程正常结束，获取对应的退出码
	//		printf("exit code: %d\n",WEXITSTATUS(status));
	//	}
	//}

	// if(ret>0)
	// {
	// 	printf("father process wait:%d, success,status:%d ,status exit signal:%d \n",ret,(status>>8)&0xFF,status&0xFF);
	// }
	// else
	// {
	// 	printf("father wait failed!\n");
	// }
	return 0;
}
//int main()
//{
//	pid_t id = fork();
//	if(id == 0)
//	{
//		//child
//		int cnt = 5;
//		while(cnt)
//		{
//			printf("child[%d] is running: cnt is : %d\n",id,cnt);
//			cnt--;
//			sleep(1);
//		}
//		exit(0);
//	}
//	//parent
//	sleep(10);
//	printf("father wait begin!\n");
//	pid_t ret = wait(NULL);
//	if(ret>0)
//	{
//		printf("father process wait:%d, success\n",ret);
//	}
//	else
//	{
//		printf("father wait failed!\n");
//	}
//	sleep(10);
//	return 0;
//}

// int main()
// {
// 	_exit(123);	

// 	return 0;
// }

// int fun()
// {
// 	printf("test\n");
// 	return 1;
// }
// int main()
// {
// 	fun();
// 	exit(12);	
// 	return 0;
// }

// int main()
// {
// 	int a = 1;
// 	a/=0;
// 	return 0;
// }

// int main()
// {
// 	for(int i=0;i<140;i++)
// 	{
// 		printf("%d:%s\n",i,strerror(i));
// 	}
// 	return 123;
// }
