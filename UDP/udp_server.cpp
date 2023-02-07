#include <iostream>
#include <cstdio>
#include <cerrno>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// const uint16_t port = 8080;

void Usage(std::string proc)
{
    std::cout << "Usage: " << proc << " port" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
        return 1;
    }

    uint16_t port = atoi(argv[1]);
    // 1.创建套接字,打开网络文件
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        std::cerr << "socket create error: " << errno << std::endl;
        return 1;
    }

    // std::cout << sock << std::endl;
    // 2.给服务器绑定端口和ip(特殊处理)

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port); // 此处的端口号, 是我们计算机上的变量,是主机序列
    // 需要将点分十进制的字符串风格IP地址,转换为4字节整数IP
    // 也要考虑大小端
    // in_addr_t inet_addr(const char* cp) 用来完成上述工作

    // 注意:云服务器不允许用户直接bind公网IP, 另外我们实际正常编写的时候,我们也不会指明IP
    // local.sin_addr.s_addr = inet_addr("101.43.176.53"); //(点分十进制,字符串风格[0~255].[0~255].[0~255].[0~255])
    // INADDR_ANY: 如果你bind的是确定的IP(主机), 意味着只有发送到该IP主机上面的数据
    // 才会交给你的网络进程, 但是,一般服务器可能有多张网卡,配置多个IP,我们需要的不是某个IP上面的数据
    // 我们需要的是,所有发送到该主机,发送到该端口的数据
    local.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0)
    {
        std::cerr << "bind error:" << errno << std::endl;
        return 2;
    }

    // 3.提供服务
    bool quit = false;
#define NUM 1024
    char buffer[NUM];
    while (!quit)
    {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);

        // 注意:我们默认认为通信的数据是双方在互发字符串

        ssize_t cnt = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&peer, &len);

        if (cnt > 0)
        {
            buffer[cnt] = 0; // 可以当做一个字符串命令

            FILE *fp = popen(buffer, "r");
            std::string echo_hello;
            char line[2048] = {0};
            while (fgets(line, sizeof(line), fp) != NULL)
            {
                echo_hello += line;
            }

            // if (feof(fp))
            // {
            //     //读取结果

            // }

            pclose(fp);

            std::cout << "clent# " << buffer << std::endl;

            // // 根据用户输入, 构建一个新的字符串
            // std::string echo_hello = buffer;
            echo_hello += "...";
            sendto(sock, echo_hello.c_str(), echo_hello.size(), 0, (struct sockaddr *)&peer, len);
        }
        else
        {
        }
    }

    return 0;
}