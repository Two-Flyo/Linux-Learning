#include "Sock.hpp"

#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>

// 其中wwwroot 就叫做web根目录. wwwroot目录下放置的内容,就是web根目录
// wwwroot目录下的index.html 就是网站的首页

#define WWWROOT "./wwwroot/"
#define HOME_PAGE "index.html"
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

    ssize_t s = recv(sock, buffer, sizeof(buffer) - 1, 0);

    if (s > 0)
    {
        buffer[s] = 0;
        std::cout << buffer << std::endl; // 查看http的请求格式

        // std::string response = "http/1.1 301 Permanently moved\n";
        std::string response = "http/1.1 302 Found\n";
        response += "Location: https://www.baidu.com/\n";
        response += "\n";
        send(sock, response.c_str(), response.size(), 0);

        // std::string http_response = "http/1.0 200 OK\n";
        // http_response += "Content-Type: text/plain\n"; // text/plain 正文是普通的文本
        // http_response += "\n";                         // 空行
        // http_response += "hello lrf ~ ~ ~";

        // send(sock, http_response.c_str(), http_response.size(), 0);

        //     std::string html_file = WWWROOT;
        //     html_file += HOME_PAGE;
        //     struct stat st;
        //     stat(html_file.c_str(), &st);
        //     // 返回的时候, 不仅仅是返回正文网页信息, 而是还要包括http请求
        //     std::string http_response = "http/1.0 200 OK\n";

        //     // 正文部分类型
        //     http_response += "Content-Type: text/html; charset=utf8\n";
        //     http_response += "Content-Length: ";
        //     http_response += std::to_string(st.st_size);
        //     http_response += "\n";
        //     http_response += "\n";

        //     // 接下来才是正文
        //     std::ifstream in(html_file);
        //     if (!in.is_open())
        //     {
        //         std::cerr << "open html error!" << std::endl;
        //     }
        //     else
        //     {
        //         std::string content;
        //         std::string line;
        //         while (std::getline(in, line))
        //         {
        //             content += line;
        //         }
        //         http_response += content;
        //         in.close();

        //         send(sock, http_response.c_str(), http_response.size(), 0);
        //     }
        // }

        close(sock);
        return nullptr;
    }
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