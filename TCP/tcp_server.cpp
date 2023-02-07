#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <cerrno>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>

void ServiceIO(int new_sock)
{
    while (true)
    {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        ssize_t s = read(new_sock, buffer, sizeof(buffer) - 1);

        if (s > 0)
        {
            buffer[s] = 0; // 将获取的内容当成字符串
            std::cout << "client# " << buffer << std::endl;

            std::string echo_string = ">>>server<<<, ";
            echo_string += buffer;

            write(new_sock, echo_string.c_str(), echo_string.size());
        }
        else if (s == 0)
        {
            std::cout << "client quit ..." << std::endl;
            break;
        }
        else
        {
            std::cerr << "read error" << std::endl;
            break;
        }
    }
}

void Usage(std::string proc)
{
    std::cout << "Usage: " << proc << " port" << std::endl;
}

// ./tcp_server 8081
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        Usage(argv[0]);
    }

    // 1.创建套接字
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock < 0)
    {
        std::cerr << "socket error" << errno << std::endl;
        return 2;
    }

    // 2.bind:绑定
    struct sockaddr_in local;
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(argv[1]));
    local.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_sock, (sockaddr *)&local, sizeof(local)) < 0)
    {
        std::cerr << "bind error" << errno << std::endl;
    }

    // 3.因为TCP是面向连接的, a.在通信前需要建立连接, b.然后才能通信
    // 一定有人主动建立(客户端, 需要服务),一定有人被动接受连接(服务器,提供服务)
    // 我们当前写的是server, 周而复始不间断的等待客户到来
    // 我们要不断的给用户提供一个建立连接的功能
    //
    // 设置套接字是Listen状态, 本质是允许用户连接

    const int back_log = 5;
    if (listen(listen_sock, back_log) < 0)
    {
        std::cerr << "listen error" << std::endl;
        return 4;
    }

    signal(SIGCHLD, SIG_IGN);  //在Linux中,父进程忽略子进程的SIGCHLD,子进程会自动退出释放资源

    for (;;)
    {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int new_sock = accept(listen_sock, (struct sockaddr *)&peer, &len);

        if (new_sock < 0)
        {
            continue;
        }

        uint16_t cli_prot = ntohs(peer.sin_port);
        std::string cli_ip = inet_ntoa(peer.sin_addr);

        std::cout << "get a new link -> : [" << cli_ip  << ":" << cli_prot << "]# " << new_sock << std::endl;


        //version 2.0版本
        pid_t id = fork();
        if (id < 0)
        {
            continue;
        }
        else if(id == 0) 
        {
            //child process
            ServiceIO(new_sock);

            //曾经被父进程打开的fd, 是否会被子进程继承呢?   
            //无论父子进程中的哪一个,强烈建议关闭,防止误读


            close(new_sock);
            exit(0);
        }
        else
        {
            //father
            // Do Nothing
            close(new_sock);
        }

        // version 1.0:单进程版, 没人使用
        // 提供服务
        // ServiceIO(new_sock);

    }

    return 0;
}