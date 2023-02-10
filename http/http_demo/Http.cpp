// #include "Sock.hpp"
// #include <pthread.h>

// void Usage(std::string proc)
// {
//     std::cout << "Usage: " << proc << " port" << std::endl;
// }

// void *HandlerHttpRequest(void *args)
// {
//     // Http协议，如果自己写的话，本质是，我们要根据协议内容，来进行文本分析！

//     int sock = *(int *)args;
//     delete (int *)args;
//     pthread_detach(pthread_self());

// #define SIZE 1024 * 10

//     char buffer[SIZE];
//     memset(buffer, 0, sizeof(buffer));

//     ssize_t s = recv(sock, buffer, sizeof(buffer), 0);
//     if (s > 0)
//     {
//         buffer[s] = 0;
//         std::cout << buffer; // 查看http的请求格式! for test

//         send(sock, http_response.c_str(), http_response.size(), 0); // ok??
//     }

//     close(sock);
//     return nullptr;
// }

// int main(int argc, char *argv[])
// {
//     if (argc != 2)
//     {
//         Usage(argv[0]);
//         exit(1);
//     }

//     uint16_t port = atoi(argv[1]);
//     int listen_sock = Sock::Socket();
//     Sock::Bind(listen_sock, port);
//     Sock::Listen(listen_sock);

//     for (;;)
//     {
//         int sock = Sock::Accept(listen_sock);
//         if (sock > 0)
//         {
//             pthread_t tid;
//             int *parm = new int(sock);
//             pthread_create(&tid, nullptr, HandlerHttpRequest, parm);
//         }
//     }
// }

#include "Sock.hpp"
#include <pthread.h>

void Usage(std::string proc)
{
    std::cout << "Usage: " << proc << " port" << std::endl;
}

void *HandlerHttpRequest(void *args)
{
    int sock = *(int *)args;
    delete (int *)args;

    pthread_detach(pthread_self());
#define SIZE 1024 * 10
    char buffer[SIZE];
    memset(buffer, 0, sizeof(buffer));

    ssize_t s = recv(sock, buffer, sizeof(buffer), 0);

    if (s > 0)
    {
        buffer[s] = 0;
        std::cout << buffer << std::endl; // 查看http的请求格式

        std::string http_response = "http/1.0 200 OK\n";
        http_response += "Content-Type: text/plain\n"; // text/plain 正文是普通的文本
        http_response += "\n";                         // 空行
        http_response += "hello lrf ~ ~ ~";

        send(sock, http_response.c_str(), http_response.size(), 0);
    }

    close(sock);
    return nullptr;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
        exit(1);
    }

    uint16_t port = atoi(argv[1]);
    int listen_sock = Sock::Socket();
    Sock::Bind(listen_sock, port);
    Sock::Listen(listen_sock);

    for (;;)
    {
        int sock = Sock::Accept(listen_sock);
        if (sock > 0)
        {
            pthread_t tid;
            int *parm = new int(sock);
            pthread_create(&tid, nullptr, HandlerHttpRequest, (void *)parm);
        }
    }
    return 0;
}