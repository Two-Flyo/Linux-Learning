#pragma once
#include <iostream>
#include <queue>
#include <pthread.h>

namespace blockqueue
{

    const int default_t = 5;

    template <class T>
    class BlockQueue
    {
    private:
        std::queue<T> _bq;
        int _cap; // 队列元素上限
        pthread_mutex_t _mtx;
        // 1.当生产满了的时候,就应该不要生产了(不要竞争锁了),而应该让消费者消费
        // 2.当消费空了, 就不应该消费了(不要竞争锁了),而应该
        pthread_cond_t _full;  //_bq是满的, 消费者等待
        pthread_cond_t _empty; //_bq是空的,生产者等待
    private:
        bool IsFull()
        {
            return _bq.size() == _cap;
        }

        bool IsEmpty()
        {
            return _bq.size() == 0;
        }

        void LockQueue()
        {
            pthread_mutex_lock(&_mtx);
        }

        void UnlockQueue()
        {
            pthread_mutex_unlock(&_mtx);
        }

        void ProducterWait()
        {
            // pthread_cond_wait():
            //  1.调用的时候,会首先自动释放_mtx,然后在挂起
            //  2.返回的时候,会首先自动竞争锁,获取到锁之后,才能返回
            pthread_cond_wait(&_empty, &_mtx);
        }

        void ConsumerWait()
        {
            pthread_cond_wait(&_full, &_mtx);
        }

        void WakeupConsumer()
        {
            pthread_cond_signal(&_full);
        }

        void WakeupProducter()
        {
            pthread_cond_signal(&_empty);
        }

    public:
        BlockQueue(int cap = default_t)
            : _cap(cap)
        {
            pthread_mutex_init(&_mtx, nullptr);
            pthread_cond_init(&_full, nullptr);
            pthread_cond_init(&_empty, nullptr);
        }
        ~BlockQueue()
        {
            pthread_mutex_destroy(&_mtx);
            pthread_cond_destroy(&_full);
            pthread_cond_destroy(&_empty);
        }

        void Push(const T &in)
        {

            LockQueue();
            // 需要进行条件检测的时候,这里需要使用循环方式,
            // 以此保证退出循环一定是因为条件不满足所导致
            while (IsFull())
            {
                ProducterWait();
            }
            // 向队列中放数据,生产函数
            _bq.push(in);

            // if (_bq.size() > _cap / 2)
            WakeupConsumer();

            UnlockQueue();

            //
        }

        void Pop(T *out)
        {
            LockQueue();
            while (IsEmpty())
            {
                // 无法消费
                ConsumerWait();
            }
            // 从队列中拿数据,消费函数
            *out = _bq.front();
            _bq.pop();

            // if (_bq.size() / 2 < _cap)
            WakeupProducter();

            UnlockQueue();
        }
    };
}
