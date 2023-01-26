#include "comm.h"

int main()
{
	int fd = open(MY_FIFO, O_WRONLY); // 不需要O_CREAT
	if(fd < 0)
	{
		perror("open file");
		return 1;
	}

	//业务逻辑
	while(1)
	{
		printf("请输入# ");
		fflush(stdout);
		char buffer[64] = {0};
		ssize_t s =  read(0, buffer, sizeof(buffer) - 1);
		if(s > 0)
		{
			buffer[s - 1] = 0;
			printf("%s\n", buffer);
			// 拿到了数据
			write(fd, buffer, strlen(buffer)); 
		}
		else if(s == 0)
		{

		}
	}

	close(fd);
	return 0;
}
