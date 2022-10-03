#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int g_val = 100;

int main()
{
	//数据是私有的,修改时发生写时拷贝
	if(fork() == 0)
	{
		//child
		int cnt = 5;
		while(cnt)
		{
			printf("i am child,times: %d\n, g_val = %d, &g_val = %p\n",cnt, g_val, &g_val);
			sleep(1);
			cnt--;
			if(cnt == 3)
			{
				printf("####################child更改数据########################\n");
				g_val = 200;
				printf("####################child更改数据########################\n");
			}
		}
	}
	else
	{
		//parent
		while(1)
		{
			printf("i am parent, g_val = %d, &g_val = %p\n", g_val, &g_val);
			sleep(1);
		}
	}
	return 0;
}
