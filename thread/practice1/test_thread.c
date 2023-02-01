#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void* thread_run(void* args)
{
	const char* id = (const char*)args;
	while(1)
	{
		printf("%s  pid:%d\n", id ,getpid());
		sleep(1);
	}
}

int main()
{
	pthread_t tid;
	pthread_create(&tid, NULL, thread_run, (void*)"thread 1");
	while(1)
	{
		printf("thread -> main  pid:%d \n", getpid());
		sleep(1);
	}
	return 0;
}
