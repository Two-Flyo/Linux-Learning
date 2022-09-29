#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main()
{
	pid_t id = fork();
	if(id == 0)
	{
		//child
		while(true)
		{
			cout<<"i am child ,running"<<endl;
			sleep(2);
		}
	}
	else
	{
		//parent
		cout<<"father do nothing"<<endl;
		sleep(1);
	}
	return 0;
}

// int main()
// {
// 	while(true)
// 	{
// 		cout<<"hello"<<endl;
// 	}
// 	return 0;
// }


// int main()
// {
// 	while(1)
// 	{
// 		sleep(10);
// 	}

// 	return 0;
// }


//int main()
//{
//	pid_t id = fork();
//	if(id == 0)
//	{
//		//childi
//		while(true)
//		{
//			cout<<"i am child ,pid: "<<getpid()<<"my parend pid: "<<getppid()<<endl;
//			sleep(1);
//		}
//	}
//	else if(id > 0)
//	{
//		// parent
//		while(true)
//		{
//			cout<<"i am parent ,pid: "<<getpid()<<"my parend pid: "<<getppid()<<endl;
//			sleep(1);		
//		}
//	}
//	else
//	{
//		//TODO
//	}

//	return 0;
//}


// int main()
// {
// 	pid_t id =fork();
// 	cout<<"hello proc:"<<getpid()<<"hello parent"<<getppid()<<"ret: "<<id<<endl;
	
// 	return 0;
// }
