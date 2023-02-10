#pragma once

#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Sock
{
public:
    static int Socket()
    {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
            std::cerr << "socket error" << std::endl;
            exit(2);
        }

        return sock;
    }

    static void Bind(int sock, uint16_t port)
    {
        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        local.sin_addr.s_addr = INADDR_ANY;

        if (bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0)
        {
            std::cerr << "bind error" << std::endl;
            exit(3);
        }
    }

    static void Listen(int sock)
    {
        if (listen(sock, 5) < 0)
        {
            std::cerr << "listen error" << std::endl;
            exit(4);
        }
    }

    static int Accept(int sock)
    {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int fd = accept(sock, (struct sockaddr *)&peer, &len);
        if (fd >= 0)
        {
            return fd;
        }
        return -1;
    }

    static void Connect(int sock, std::string ip, uint16_t port)
    {
        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));

        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        server.sin_addr.s_addr = inet_addr(ip.c_str());

        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == 0)
        {
            std::cout << "Connect Success!" << std::endl;
        }
        else
        {
            std::cout << "Connect Failed!" << std::endl;
            exit(5);
        }
    }
};