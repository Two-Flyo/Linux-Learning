#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main()
{
	int fd1 = open("./log.txt", O_WRONLY | O_CREAT, 0664);
	int fd2 = open("./log.txt", O_WRONLY | O_CREAT, 0664);
	int fd3 = open("./log.txt", O_WRONLY | O_CREAT, 0664);
	int fd4 = open("./log.txt", O_WRONLY | O_CREAT, 0664);
	int fd5 = open("./log.txt", O_WRONLY | O_CREAT, 0664);
	int fd6 = open("./log.txt", O_WRONLY | O_CREAT, 0664);
	printf("fd1:%d\n",fd1);
	printf("fd2:%d\n",fd2);
	printf("fd3:%d\n",fd3);
	printf("fd4:%d\n",fd4);
	printf("fd5:%d\n",fd5);
	printf("fd6:%d\n",fd6);
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	close(fd5);
	close(fd6);
	return 0;
}






// #include <iostream>
// #include <string>
// #include <fstream>

// using namespace std;

// int main()
// {
// 	std::ofstream out("./log.txt",ios::out | ios::binary);
// 	if(!out.is_open())
// 	{
// 		cerr<<"open error"<<endl;
// 		return 1;
// 	}
// 	int n  = 10;
// 	while(n--)
// 	{
// 		string msg = "hello world!";
// 		out.write(msg.c_str(),msg.size());	
// 	}
// 	out.close();
// 	return 0;

// }
