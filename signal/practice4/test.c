#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void getChild(int signo)
{
	printf("get a signal :%d  pid:%d\n", signo, getpid());
}
	

int main()
{
	signal(SIGCHLD, getChild);
	pid_t pid = fork();
	if(pid == 0)
	{
		//child process
		int cnt = 5;
		while(cnt)
		{
			printf("我是子进程: %d\n", getpid());
			sleep(1);
			cnt--;
		}
		exit(0);
	}

	while(1);

	return 0;
}

