#include <stdio.h>
#include <signal.h>

volatile int flag = 0;

void handler(int signo)
{
	flag = 1;
	printf("change flag 0 -> 1\n");
}

int main()
{
	signal(2, handler);

	while(!flag);

	printf("进程正常退出!\n");
	return 0;
}
