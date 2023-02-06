#include "thread_pool.hpp"
#include "task.hpp"
#include <ctime>
#include <cstdlib>

using namespace task;
using namespace threadpool;

int main()
{
    ThreadPool<Task> *tp = new ThreadPool<Task>(1000);
    tp->InitThreadPool();

    srand((long long)time(nullptr));

    while (true)
    {
        // 网络
        Task t(rand() % 20 + 1, rand() % 10 + 1, "+-*/%"[rand() % 5]);
        tp->PushTask(t);
        // sleep(1);
    }

    return 0;
}