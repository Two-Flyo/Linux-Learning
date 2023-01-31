#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
int count = 0;

void HandlerAlarm(int sig)
{
	printf("hello: %d\n",count);
	exit(1);
}

int main()
{
	signal(SIGALRM, HandlerAlarm);
	alarm(1); //没有设置alram信号的捕捉动作,执行默认动作,终止进程
	while(1)
	{
		count++;
		// printf("hello : %d\n", count++);
		
	}
	return 0;
}



// static void Usage(const char *proc)
// {
// 	printf("Usage: \n\t %s signo who\n", proc);
// }

// void handler(int sig)
// {
// 	printf("signal no:%d", sig);
// }

// int main()
// {
// 	for(int sig = 1; sig <= 31; sig++)
// 	{
// 		signal(sig, handler);
// 	}
// 	int ret = alarm(30);

// 	while(1)
// 	{
// 		printf("I am a process ret=%d\n", ret);
// 		sleep(1);

// 		ret = alarm(0);
// 	}
// }

// 
// int main(int argc, char* argv[])
// {
	// while(1)
	// {
	// 	printf("I am a process\n");
	// 	sleep(3);
	// 	raise(8);
	// }



	// if(argc != 3)
	// {
	// 	Usage(argv[0]);
	// 	return 1;
	// }

	// int signo = atoi(argv[1]);
	// int who = atoi(argv[2]);

	// kill(who, signo);

	// printf("signo: %d who: %d\n", signo, who);

	// return 0;
// }



// int main()
// {
// 	if(fork() == 0)
// 	{
// 		while(1)
// 		{
// 			printf("I am child process...\n");
// 			int a = 10;
// 			a /= 0;
// 		}
// 	}

// 	int status = 0;
// 	waitpid(-1, &status, 0);

// 	printf("exit code:%d  exit singal:%d  code dump:%d\n", (status >> 8) & 0xff, (status & 0x7f), (status >> 7) & 1);
	
// 	return 0;
// }


// void handler(int signal)
// {
// 	printf("get a signal: signal no: %d\n", signal);
// }

// int main()
// {
	// for(int i = 1; i <= 31; i++)
	// {
	// 	signal(i, handler);
	// }
	//通过signal注册对2号信号的处理动作，改成我们的自定义动作
	// signal(2, handler);
	// while(1)
	// {
	// 	printf("hello world!\n");
	// 	sleep(1);
	// }
	// int a = 123;
	// a /= 0;
	// return 0;
// }
