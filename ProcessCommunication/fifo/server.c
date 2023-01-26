#include "comm.h"
#include <unistd.h>

int main()
{
	umask(0);
	if(mkfifo(MY_FIFO, 0666) < 0)
	{
		perror("mkfifo error");
		return 1;
	}

	int fd = open(MY_FIFO, O_RDONLY);

	if(fd < 0)
	{
		perror("open");
		return 2;
	}

	// 业务逻辑, 可以进行读写操作了~~~

	while(1)
	{
		char buffer[64] = {0};
		ssize_t s = read(fd, buffer, sizeof(buffer) - 1);
		if(s > 0)
		{
			//success
			buffer[s] = 0;
			if(strcmp(buffer, "show") == 0)
			{
				if(fork() == 0)
				{
					execl("/usr/bin/ls", "ls", "-a", NULL);
					exit(1);
				}

				waitpid(-1, NULL, 0);
			}

			else if(strcmp(buffer, "tree") == 0)
			{
				if(fork() == 0)
				{
					execlp("tree", "tree", NULL);
					exit(1);
				}
				
			}
			printf("client# %s\n", buffer);
		}
		else if(s == 0)
		{
			//peer close
			printf("client quit ...\n");
		}
		else
		{
			//error
			perror("read error");
			break;
		}
	}

	close(fd);
	
	return 0;
}
