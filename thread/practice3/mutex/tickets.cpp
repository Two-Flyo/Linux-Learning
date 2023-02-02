#include <iostream>
#include <pthread.h>
#include <mutex>
#include <unistd.h>
#include <ctime>
#include <stdlib.h>
#include <string>

class Ticket
{
private:
    int tickets;
    pthread_mutex_t mtx;//原生线程库,系统级别
    // std::mutex cppmtx;//c++语言级别

    //int lock;// lock--申请锁, lock++释放锁 if(lock > 0) lock--;
public:
    Ticket()
        : tickets(1000)
    {
        pthread_mutex_init(&mtx, nullptr);
    }
    ~Ticket()
    {
        pthread_mutex_destroy(&mtx);
    }

    bool GetTicket()
    {
        //bool类型的变量是否被所以线程共享呢?
        bool res = true;
        
        // cppmtx.lock();
        // 我要访问临界资源tickets的时候,需要先访问mtx, 前提是所有的线程必须得先看到他
        // 那么锁本身, 是不是也是临界资源呢?
        // 你如何保证锁本身是安全的?
        // 原理: lock unlock -> 是原子的


        pthread_mutex_lock(&mtx);
        //执行这部分代码的执行流,就是互斥的!
        if (tickets > 0)
        {
            usleep(1000);
            std::cout << "我是[" << pthread_self() << "]我要抢的票是: " << tickets << std::endl;
            tickets--;
        }
        else
        {
            std::cout << "票已售罄" << std::endl;
            res = false;
        }
        // cppmtx.unlock();
        pthread_mutex_unlock(&mtx);
        return res;
    }
};

// 抢票逻辑:10000票, 5个线程同时在抢
void *ThreadRoutine(void *args)
{
    Ticket *t = (Ticket *)args;
    while (true)
    {
       if(!t->GetTicket())
        break;
    }
    
}

int main()
{
    Ticket *t = new Ticket;
    pthread_t tid[5];
    for (int i = 0; i < 5; i++)
    {
        int *id = new int(i);
        pthread_create(tid + i, nullptr, ThreadRoutine, (void *)t);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(tid[i], nullptr);
    }

    return 0;
}
