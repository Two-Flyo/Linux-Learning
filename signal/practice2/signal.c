#include <bits/types/siginfo_t.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void handler(int signo)
{
	printf("get a signo: %d\n", signo);
}

int main()
{
	struct sigaction act;
	memset(&act, 0, sizeof(act));
		
	act.sa_handler = handler;
	sigemptyset(act.sa_mask);

	sigaddset(&act.sa_mask, 3);
	//本质是修改当前进程的handler函数指针数组的特定内容
	sigaction(2, &act, NULL);

	while(1)
	{
		printf("hello world!\n");
		sleep(1);
	}


	return 0;
}

//void show_pending(sigset_t *set)
//{
//	printf("curr process pending: ");
//	for(int i = 1; i <= 31; i++)
//	{
//		if(sigismember(set, i))
//			printf("1");
//		else
//			printf("0");
//	}

//	printf("\n");
//}

//void handler(int signo)
//{
//	printf("%d号信号已递达,已被处理完成!\n", signo);
//}

//int main()
//{
//	//虽然sigset_t 是一个位图结构,但是不同的OS实现是不一样的,不能让用户直接修改该变量
//	//需要使用特定的函数
	
//	//set是一个变量, 该变量在什么地方保存?
	
//	sigset_t iset, oset;

	
//	signal(2, handler);

//	sigemptyset(&iset);
//	sigemptyset(&oset);

//	sigaddset(&iset, 2);
//	// sigaddset(&iset, 9);

//	//1.设置当前进程的屏蔽字
//	//2.获取当前进程老的屏蔽字
//	sigprocmask(SIG_SETMASK, &iset, &oset);
	
//	sigset_t pending;
//	int count = 0;

//	while(1)
//	{
//		sigemptyset(&pending);

//		sigpending(&pending);

//		show_pending(&pending);

//		sleep(1);
//		count++;
//		if(count == 20)
//		{
//			sigprocmask(SIG_SETMASK, &oset, NULL);
//			//2号信号的默认动作是终止进程,所以我们看不到恢复后的pending
//			printf("取消对2号信号的阻塞\n");
			
//		}
//	}

//	// set |= 1;
//	return 0;
//}
