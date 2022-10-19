#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>


int main()
{
	int fd = open("./log.txt", O_WRONLY);
	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	dup2(fd, 1);  //把本来应该显示到显示器的内容,写入到文件中
	printf("hello printf\n");
	fprintf(stdout, "hello fprintf\n");
	fputs("hello puts", stdout);
		
	// close(0);
	// int fd = open("./log.txt", O_RDONLY);

	// printf("fd = %d\n", fd);
	// char line[128];
	// while(fgets(line,sizeof(line)-1,stdin))
	// {
	// 	printf("%s",line);
	// }
	// int fd = open("./log.txt", O_CREAT | O_WRONLY |O_APPEND, 0664);
	// printf("%d\n", fd);
    // fprintf(stdout, "hello");


	return 0;
}

// int main()
// {
// 	char buffer[64];
// 	const char* msg = "hello world!\n";
// 	printf("len(str)=%lu\n", strlen(msg));
// 	read(0, buffer, sizeof(buffer));
// 	printf("len(buffer)=%lu\n", strlen(buffer));
// 	printf("%lu",strlen("\0\0\0\0"));
// 	return 0;
// }
// int main()
// {
// 	char buffer[64];
// 	read(0, buffer, sizeof(buffer));
// 	// printf("len(str) = %lu",strlen(buffer));
// 	printf("%lu",strlen("hello world!\n"));
// 	buffer[strlen(buffer)-1] = 0;
// 	printf("echo: %s\n",buffer);
// 	// const char *msg = "hello world!\n";
// 	// write(1, msg, strlen(msg));
// 	// write(1, msg, strlen(msg));
// 	// write(2, msg, strlen(msg));
// 	// write(2, msg, strlen(msg));
// 	return 0;
// }

// int main()
// {
// 	int fd = open("./log.txt", O_RDONLY);
// 	if(fd < 0)
// 	{
// 		perror("open");
// 		return 1;
// 	}
// 	char buffer[1024];
//     ssize_t s =	read(fd, buffer, sizeof(buffer)-1);
// 	if(s > 0)
// 	{
// 		buffer[s] = 0;
// 		printf("%s",buffer);
// 	}


// 	close(fd);
// 	return 0;
// }

// int main()
// {
// 	int fd = open("./log.txt", O_CREAT|O_WRONLY);
// 	if(fd < 0 )
// 	{
// 		perror("open");
// 		return 1;
// 	}
// 	const char *msg = "hello world!";
// 	int cnt = 5;
// 	while(cnt)
// 	{
// 		write(fd, msg, strlen(msg));
// 		cnt--;
// 	}
// 	close(fd);

// 	return 0;
// }
