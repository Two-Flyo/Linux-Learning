#include <stdio.h>

int main()
{
	const char *msg = "you can see me!\n";
	fputs(msg, stderr);

	return 0;
}

// int main()
// {
// 	FILE *fp = fopen("./log.txt", "a");
// 	if(fp == NULL)
// 	{
// 		perror("fopen:");
// 		return 1;
// 	}
		



	// char buffer[64];
	// while(fgets(buffer, sizeof(buffer), fp))
	// {
	// 	printf("%s",buffer);
	// }

	// if(!feof(fp))
	// {
	// 	printf("fgets quit not normal!\n");
	// }
	// else
	// {
	// 	printf("fget quit normal!\n");
	// }

	// const char *msg = "23333 ~ \n";
	// int n = 10;
	// while(n--)
	// {
	// 	fputs(msg, fp);
	// }

	// fclose(fp);
	// return 0;
// }
