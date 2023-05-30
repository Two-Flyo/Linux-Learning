#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>



void *thread_run(void* args)
{
	while(1)
	{
		printf("main thread_id: 0x%x\n", pthread_self());
		sleep(2);
	}
}


int main()
{
	pthread_t tid;
	pthread_create(&tid, NULL, thread_run, "new thread");

	while(1)
	{
		printf("thread id: 0x%x\n", pthread_self());
		sleep(1);
	}
	return 0;
}


//pthread_t g_id;

//void *thread_run(void* args)
//{
//	pthread_detach(pthread_self());
//	int num = *(int*)args;
//	while(1)
//	{
//		printf("我是新线程[%d] 我的线程ID是: %lu\n", num, pthread_self());
//		sleep(2);
//		// pthread_cancel(g_id);
//		//野指针问题
//		// break;
//		// if(num == 3)
//		// {
//		// 	printf("thread number: %d\n quit", num);
//		// 	int *p = NULL;
//		// 	*p = 123;
//		// }		
//	}

//	pthread_exit((void*)123);

//	return (void*)111; 
//}

//#define NUM 1



//int main()
//{
//	g_id = pthread_self();
//	pthread_t tid[NUM];
//	for(int i = 0; i < NUM; i++)
//	{
//		pthread_create(&tid[i], NULL, thread_run, (void*)&i);
//		sleep(1);
//	}

//	printf("wait sub thread...\n");
//	sleep(1);

//	printf("cancel sub thread...\n");
//	pthread_cancel(g_id);

//	void *status = NULL;
	
//	int ret = 0;

//	for(int i = 0; i < NUM; i++)
//	{
//		ret = pthread_join(tid[i], &status);
//	}
//	printf("ret=%d status=%d\n",ret, (int)status);

//	// while(1)
//	// {
//	// 	printf("我是主线程, 我的线程ID是: %lu \n",  pthread_self());
//	// 	printf("#####################begin######################\n");
//	// 	for(int i = 0; i < NUM; i++)
//	// 	{
//	// 		printf("我是主线程, 我创建的线程是[%d], 线程ID是: %lu \n", i, tid[i]);
//	// 	}
//	// 	printf("######################end#######################\n");
//	// 	sleep(1);
//	// }

//	return 0;
//}
