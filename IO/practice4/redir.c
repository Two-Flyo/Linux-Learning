#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
	const char* msg = "hello stdout\n";
	//系统调用接口
	write(1, msg, strlen(msg));
	//C语言提供的接口
	printf("hello printf\n");
	fprintf(stdout, "hello fprintf\n");
	fputs("hello puts\n", stdout);
	fflush(stdout);

	fork();
	return 0;
}


// int main()
// {
// 	close(1);
// 	int fd = open("./log.txt",O_CREAT | O_WRONLY, 0664);
// 	printf("fd = %d\n", fd);
// 	fprintf(stdout, "hello world!\n");
// 	fprintf(stdout, "hello world!\n");
// 	fprintf(stdout, "hello world!\n");
// 	fprintf(stdout, "hello world!\n");
// 	fprintf(stdout, "hello world!\n");
// 	fprintf(stdout, "hello world!\n");
// 	fflush(stdout);

// 	close(fd);
// 	return 0;
// }



// int main()
// {
// 	const char* msg1 = "hello 标准输出!\n";
// 	write(1, msg1, strlen(msg1));

// 	const char *msg2 = "hello 标准错误\n";
// 	write(2, msg2, strlen(msg2));
	
// 	close(1);
// 	return 0;
// }
