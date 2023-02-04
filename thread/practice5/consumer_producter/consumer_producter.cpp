#include "blockqueue.hpp"
#include <cstdlib>
#include <unistd.h>
#include "task.hpp"

using namespace blockqueue;
using namespace task;

void *consumer(void *args)
{
    BlockQueue<Task> *bq = (BlockQueue<Task> *)args;
    while (true)
    {
        // 2.获取任务
        Task t;
        bq->Pop(&t);  //这里完成了消费的第一步
        t();
        // t.Run();
        // sleep(1);
        // int data = 0;
        // bq->Pop(&data);
        // +

        //     std::cout
        //     << "消费者消费数据: " << data << std::endl;
    }
}

void *producter(void *args)
{
    BlockQueue<Task> *bq = (BlockQueue<Task> *)args;
    std::string ops = "+-*/%";
    while (true)
    {
        // 1.制造数据,生产者数据从哪里来?
        int x = rand() % 20 + 1; //[1 - 20]
        int y = rand() % 10 + 1; //[1 - 10]
        char op = ops[rand() % 5];
        Task t(x, y, op);
        std::cout << "生产者派发了一个任务: " << x << " " << op << " " << y << " = ?" << std::endl;
        //2.将数据派发到任务队列中去
        bq->Push(t);
        sleep(1);
        // sleep(1);
        // // 制造数据
        // int data = rand() % 20 + 1;
        // std::cout << "生产者生产数据: " << data << std::endl;
        // bq->Push(data);
    }
}

int main()
{

    srand((long long)time(nullptr));

    BlockQueue<Task> *bq = new BlockQueue<Task>();

    pthread_t c1, c2, c3, c4, c5, p;
    pthread_create(&c1, nullptr, consumer, (void *)bq);
    pthread_create(&c2, nullptr, consumer, (void *)bq);
    pthread_create(&c3, nullptr, consumer, (void *)bq);
    pthread_create(&c4, nullptr, consumer, (void *)bq);
    pthread_create(&c5, nullptr, consumer, (void *)bq);
    pthread_create(&p, nullptr, producter, (void *)bq);

    pthread_join(c1, nullptr);
    pthread_join(c2, nullptr);
    pthread_join(c3, nullptr);
    pthread_join(c4, nullptr);
    pthread_join(c5, nullptr);
    pthread_join(p, nullptr);

    return 0;
}
