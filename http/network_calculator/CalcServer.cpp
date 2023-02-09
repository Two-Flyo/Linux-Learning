#include "Protocal.hpp"
#include "Sock.hpp"
#include <pthread.h>

static void Usage(std::string proc)
{
    std::cout << "Usage: " << proc << " port" << std::endl;
    exit(1);
}

void *HandlerRequest(void *args)
{
    int sock = *(int *)args;
    delete (int *)args;

    pthread_detach(pthread_self());

    // verssion1 原生方法,没有明显的序列化和反序列化的过程
    // 业务逻辑, 做一个短服务, request -> 分析处理 -> 构建response -> sent(response) -> close(sock)
    // 1. 读取请求

    char buffer[1024];
    request_t req;
    ssize_t s = read(sock, buffer, sizeof(buffer) - 1);
    if (s > 0)
    {
        buffer[s] = 0;
        std::cout << "get a new request" << buffer << std::endl;
        std::string str = buffer;
        DeserializeRequest(str, req);

        request_t req;
    }

    // request_t req;
    // ssize_t s = read(sock, &req, sizeof(req));

    // if (s == sizeof(req))
    // {
    // 读取到了完整请求,待定
    //  req.x, req.y, req.op

    // 2.分析请求 && 3.计算结果
    response_t resp = {0, 0};

    switch (req.op)
    {
    case '+':
        resp.result = req.x + req.y;
        break;
    case '-':
        resp.result = req.x - req.y;
        break;
    case '*':
        resp.result = req.x * req.y;
        break;
    case '/':
        if (req.y == 0)
            resp.code = -1; // 表示除0
        else
            resp.result = req.x / req.y;
        break;
    case '%':
        if (req.y == 0) // 表示 mod 0
            resp.code = -2;
        else
            resp.result = req.x % req.y;
        break;
    default:
        resp.code = -3; // 代表请求方法异常
        break;
    }
    // 4.构建响应,并进行返回
    std::cout << "request: " << req.x << " " << req.op << " " << req.y << std::endl;

    // 序列化
    std::string send_str = SerializeRespone(resp); // 序列化之后

    write(sock, send_str.c_str(), send_str.size());
    std::cout << "服务结束" << send_str << std::endl;
    // }

    // 5.关闭链接
    close(sock);
}

// ./CalcServer port
int main(int argc, char *argv[])
{
    if (argc != 2)
        Usage(argv[0]);
    uint16_t port = atoi(argv[1]);

    int listen_sock = Sock::Socket();
    Sock::Bind(listen_sock, port);
    Sock::Listen(listen_sock);

    for (;;)
    {
        int sock = Sock::Accept(listen_sock);
        if (sock >= 0)
        {
            std::cout << "get a nre client ..." << std::endl;
            int *pram = new int(sock);
            pthread_t tid;
            pthread_create(&tid, nullptr, HandlerRequest, pram);
        }
    }

    std::cout << "server" << std::endl;
    return 0;
}