#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

const int NUM = 256;
const int CMD_NUM = 128;

int main()
{
	char* argv[CMD_NUM];
	char command[NUM];
	while(1)
	{
		//1.打印命令行的前置字符串
		command[0] = 0;  //'\0'的ASCII为0，所以这样可以做到O(1)的时间复杂度清空字符串
		printf("lrf@ubuntu-minishell: $");
		fflush(stdout);
		
		//2.获取命令行字符串
		fgets(command, NUM, stdin);
		command[strlen(command) - 1] ='\0';
		
		//3.解析命令行字符串
		const char *sep = " ";
		argv[0] = strtok(command, sep);
		int i = 1;
		while((argv[i] = strtok(NULL, sep)))
		{
			i++;
		}

		//4.检查命令是否需要shell本身执行的,内建命令
		if(strcmp(argv[0], "cd") ==0 )
		{
			if(argv[1] != NULL)
			{
				chdir(argv[1]);
			}
			continue;
		}
			
		// for(int i = 0;argv[i]; i++)
		//     printf("argv[%d]: %s\n", i, argv[i]);
		// 5.执行第三方命令
		if(fork() == 0)
		{
			//child process
			execvp(argv[0], argv);
			exit(1);
		}
		waitpid(-1, NULL, 0);

	}
	
	return 0;
}

