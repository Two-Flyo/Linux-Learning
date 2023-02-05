#include "ring_queue.hpp"
#include "task.hpp"
#include <pthread.h>
#include <time.h>
#include <unistd.h>

using namespace ring_queue;
using namespace task;

void *consumer(void *args)
{
    RingQueue<Task> *rq = (RingQueue<Task> *)args;
    while (true)
    {
        Task t;
        // rq->Pop();
        // int data = 0;
        rq->Pop(&t);
        // std::cout << "消费数据是: " << t.Show() << t() << " 我是 " << pthread_self() << std::endl;
        t();
        // sleep(1);
    }
}

void *producter(void *args)
{
    RingQueue<Task> *rq = (RingQueue<Task> *)args;
    const std::string ops = "+-*/%";
    while (true)
    {
        int x = rand() % 20 + 1;
        int y = rand() % 10 + 1;
        char op = ops[rand() % 5];
        // int data = rand() % 20 + 1;
        Task t(x, y, op);
        std::cout << "生产数据是: " << t.Show() << std::endl;
        rq->Push(t);
        sleep(1);
    }
}

int main()
{
    srand((long long)time(nullptr));

    RingQueue<Task> *rq = new RingQueue<Task>();

    pthread_t c1, c2, c3, c4, p1, p2, p3;
    pthread_create(&c1, nullptr, consumer, (void *)rq);
    pthread_create(&c2, nullptr, consumer, (void *)rq);
    pthread_create(&c3, nullptr, consumer, (void *)rq);
    pthread_create(&c4, nullptr, consumer, (void *)rq);
    pthread_create(&p1, nullptr, producter, (void *)rq);
    pthread_create(&p2, nullptr, producter, (void *)rq);
    pthread_create(&p3, nullptr, producter, (void *)rq);

    pthread_join(c1, nullptr);
    pthread_join(c2, nullptr);
    pthread_join(c3, nullptr);
    pthread_join(c4, nullptr);
    pthread_join(p1, nullptr);
    pthread_join(p2, nullptr);
    pthread_join(p3, nullptr);

    return 0;
}