#include "comm.h"
#include <sys/ipc.h>


int main()
{
	key_t key = ftok(PATH_NAME, PROJ_ID);
	if(key < 0)
	{
		perror("ftok error");
		return -1;
	}

	int shmid = shmget(key, SIZE, IPC_CREAT | IPC_EXCL | 0666);
	if(shmid < 0)
	{
		perror("shmget error");
		return 2;
	}

	printf("key %u, shmid: %d\n", key, shmid);
	// sleep(10);
	sleep(3);
	char* mem = (char*)shmat(shmid, NULL, 0);
	printf("attaches shm success\n");
	// sleep(15);

	//业务逻辑
	while(1)
	{
		sleep(1);
		//这里有没有调用类似pipe or fifo中的read这样的接口呢?
		printf("%s\n", mem); //认为共享内存里面放的是一个长字符串
	}


	shmdt(mem);
	printf("detaches shm success\n");
	// sleep(5);

	shmctl(shmid, IPC_RMID, NULL);

	printf("key:0x%x, shmid: %d - > shm delete success\n", key, shmid);

	// sleep(10);
	return 0;
}
