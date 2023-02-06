#include "thread_pool.hpp"
#include "task.hpp"
#include <ctime>
#include <cstdlib>

using namespace task;
using namespace threadpool;

int main()
{
    std::cout << "当前正在执行我的进程其他代码..." << std::endl;
    std::cout << "当前正在执行我的进程其他代码..." << std::endl;
    std::cout << "当前正在执行我的进程其他代码..." << std::endl;
    std::cout << "当前正在执行我的进程其他代码..." << std::endl;
    std::cout << "当前正在执行我的进程其他代码..." << std::endl;
    std::cout << "当前正在执行我的进程其他代码..." << std::endl;
    std::cout << "当前正在执行我的进程其他代码..." << std::endl;
    std::cout << "当前正在执行我的进程其他代码..." << std::endl;
    std::cout << "当前正在执行我的进程其他代码..." << std::endl;
    std::cout << "当前正在执行我的进程其他代码..." << std::endl;
    sleep(5);

    srand((long long)time(nullptr));

    while (true)
    {
        sleep(1);
        // 网络
        Task t(rand() % 20 + 1, rand() % 10 + 1, "+-*/%"[rand() % 5]);
        //单例本身会在任何场景, 任何环境下被调用
        //GetInstance()被多线程重入进而导致线程安全的问题
        ThreadPool<Task>::GetInstance()->PushTask(t);
        std::cout << ThreadPool<Task>::GetInstance() << std::endl;
    }

    return 0;
}