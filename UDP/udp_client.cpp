#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <cerrno>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void Usage(std::string proc)
{
    std::cout << "Usage: \n\t" << proc << "server_ip server_port" << std::endl;
}

// 命令行参数 ./udp_client server_ip server_port
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        return 0;
    }

    // 1.创建套接字,打开网络文件
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        std::cerr << "socket error :" << errno << std::endl;
        return 1;
    }

    // 客户端需要显示的bind吗?
    // a.首先客户端也必须要有ip和port
    // b.但是,客户端不需要显示的bind, 一旦显示bind,就必须明确,client要和哪一个port关联
    // client指明的端口号,在client端一定会有吗?? 有可能被占用,被占用导致客户端无法使用
    // server要的是port必须明确而且不变,但是client只有有就行, 一般是由OS自动给你bind()
    // client正常发送数据的时候,OS会自动给你bind,采用的是随机端口的方式!

    // 你要给谁发?
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons((atoi(argv[2])));
    server.sin_addr.s_addr = inet_addr(argv[1]);

    // 2.使用服务
    while (true)
    {
        // a.你的数据从哪里来
        // std::string message;
        // std::cout << "请输入#" << std::endl;
        // std::cin >> message;
        std::cout << "LRF-Shell $ " <<std::endl;
        char line[1024];
        fgets(line, sizeof(line), stdin);

        sendto(sock, line, strlen(line), 0, (struct sockaddr *)&server, sizeof(server));

        // 此处tmp就是一个"占位符"
        struct sockaddr_in tmp;
        socklen_t len = sizeof(tmp);
        char buffer[1024];
        ssize_t cnt = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&tmp, &len);
        if(cnt > 0)
        {
            //在网络通信中, 只有报文大小,或者字节流的个数,
            //没有C/C++字符串这样的概念(虽然我们后续可能经常会遇到类似的情况)
            buffer[cnt] = 0;
            std::cout << buffer << buffer << std::endl;
        }
        else
        {
            // TODO
            // ...
        }
    }

    std::cout << "hello client" << std::endl;
    return 0;
}