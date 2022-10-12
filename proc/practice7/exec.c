#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main()
{
	if(fork() == 0)
	{
		// char *argv[] = {"ls", "-l", NULL};
		printf("command begin...\n");
		// execl("/usr/bin/ls", "ls", "-l", NULL);
		// execv("usr/bin/ls",argv);
		// execlp("ls", "ls", "-l", NULL);
		// execvp("ls", argv);
		// execl("./exe", "exe", NULL);
		// char *env[] = {"ENV1=hello", "EVN2=world", "EVN3= ~ ", NULL};
		// execle("./exe", "exe", NULL, env);
		execl("/usr/bin/python3", "python", "test.py", NULL);
		printf("command end...\n");
		exit(1);
	}
	waitpid(-1, NULL, 0);
	printf("wait child success!\n");
	return 0;
}
