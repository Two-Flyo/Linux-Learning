#include "Protocal.hpp"
#include "Sock.hpp"

void Usage(std::string proc)
{
    std::cout << "Usage: " << proc << "server_ip "
              << "server_port" << std::endl;
}

// ./CalcClient server_ip server_port
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(1);
    }
    int sock = Sock::Socket();
    Sock::Connect(sock, argv[1], atoi(argv[2]));

    // 业务逻辑
    // while(true)
    // {
    request_t req;
    memset(&req, 0, sizeof(req));
    std::cout << "Please Enter Data One# ";
    std::cin >> req.x;
    std::cout << "Please Enter Date Two# ";
    std::cin >> req.y;
    std::cout << "Please Enter operator# ";
    std::cin >> req.op;
    std::cout << "client# " << std::endl;

    std::string json_string = SerializeRequest(req);
    ssize_t s = write(sock, json_string.c_str(), json_string.size());

    // ssize_t s = write(sock, &req, sizeof(req));
    // if(s <= 0)
    //     break;
    char buffer[1024];
    s = read(sock, buffer, sizeof(buffer) - 1);

    if(s > 0)
    {
        response_t resp;
        buffer[s] = 0;
        std::string str = buffer;
        DeserializeRespone(str, resp);
        std::cout << "code[0:success]: " << resp.code << std::endl;
        std::cout << "result: " << resp.result << std::endl;
    }
    // s = read(sock, &resp, sizeof(resp));
    // if (s == sizeof(resp))
    // {
    //     std::cout << "code[0:success]: " << resp.code << std::endl;
    //     std::cout << "result: " << resp.result << std::endl;
    // }
    //     else
    //     {
    //         break;
    //     }
    // }

    return 0;
}
