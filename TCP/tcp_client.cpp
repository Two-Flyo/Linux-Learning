#include <iostream>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void Usage(std::string proc)
{
    std::cout << "Usage" << proc << "server_ip server_port" << std::endl;
}

// ./tcp_client server_ip port
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        Usage(argv[0]);
        return 1;
    }

    std::string svr_ip =argv[1];
    uint16_t svr_port = atoi(argv[2]);

    //1.创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        std::cerr << "socker error!" << std::endl;
        return 2;
    }

    // 2. bind 3.Listen 4.accept 这样写吗????
    // client无需显示bind, client 连 server
    // client -> connect!

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(svr_port);
    server.sin_addr.s_addr = inet_addr(svr_ip.c_str());

    // 2.发起连接
    if(connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        std::cout << "connect server failed !" << std::endl;
        return 3;
    }

    std::cout << "connect success !" << std::endl;

    //进行正常的业务请求了
    while(true)
    {
        std::cout << "Please Enter# " << std::endl;
        char buffer[1024];
        fgets(buffer, sizeof(buffer) - 1, stdin);

        write(sock, buffer, strlen(buffer));
        
        ssize_t s = read(sock, buffer, sizeof(buffer) - 1);
        if(s > 0) 
        {
            buffer[s] = 0;
            std::cout << "server echo# " << std::endl;
        }
    }
    

    return 0;
}