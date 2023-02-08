#pragma once

#include <iostream>
#include <pthread.h>
#include <unistd.h>

namespace task
{
    class Task
    {
    private:
        int _sock;
    public:
        Task():_sock(-1) {}
        Task(int sock)
            :_sock(sock)
        {

        }

        int Run()
        {
            // while (true)
            // {
                char buffer[1024];
                memset(buffer, 0, sizeof(buffer));
                ssize_t s = read(_sock, buffer, sizeof(buffer) - 1);

                if (s > 0)
                {
                    buffer[s] = 0; // 将获取的内容当成字符串
                    std::cout << "client# " << buffer << std::endl;

                    std::string echo_string = ">>>server<<<, ";
                    echo_string += buffer;

                    write(_sock, echo_string.c_str(), echo_string.size());
                }
                else if (s == 0)
                {
                    std::cout << "client quit ..." << std::endl;
                    // break;
                }
                else
                {
                    std::cerr << "read error" << std::endl;
                    // break;
                }
            // }

            close(_sock);
        }
        int operator()()
        {
            return Run();
        }
        ~Task() {}
    };
}