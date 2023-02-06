#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <unistd.h>
#include <pthread.h>

namespace threadpool
{
    const int g_num = 5;
    template <class T>
    class ThreadPool
    {
    private:
        int _num;
        std::queue<T> _task_queue; // 临界资源

        pthread_mutex_t _mtx;
        pthread_cond_t _cond;

    public:
        void Lock()
        {
            pthread_mutex_lock(&_mtx);
        }

        void Unlock()
        {
            pthread_mutex_unlock(&_mtx);
        }

        bool IsEmpty()
        {
            return _task_queue.empty();
        }

        void Wait()
        {
            pthread_cond_wait(&_cond, &_mtx);
        }

        void Wakeup()
        {
            pthread_cond_signal(&_cond);
        }



    public:
        ThreadPool(int num = g_num)
            : _num(num)
        {
            pthread_mutex_init(&_mtx, nullptr);
            pthread_cond_init(&_cond, nullptr);
        }
        // 在类中,要让线程执行类内成员方法,是不可行的
        // 必须让线程执行静态方法
        static void *Rountine(void *args)
        {
            pthread_detach(pthread_self());
            ThreadPool<T> *tp = (ThreadPool<T> *)args;
            while (true)
            {   
                tp->Lock();
                while(tp->IsEmpty())
                {
                    //任务队列为空, 线程应该怎么办?
                    tp->Wait();
                }
                // 任务队列一定有任务
                T t;
                tp->PopTask(&t);
                tp->Unlock();

                t();

            }
        }

        void InitThreadPool()
        {
            pthread_t tid;
            for (int i = 0; i < _num; i++)
            {
                pthread_create(&tid, nullptr, Rountine, (void *)this);
            }
        }

        void PushTask(const T &in)
        {
            Lock();
            _task_queue.push(in);
            Unlock();
            Wakeup();
        }

        void PopTask(T* out)
        {
            *out = _task_queue.front();
            _task_queue.pop();   
        }

        ~ThreadPool()
        {
            pthread_mutex_destroy(&_mtx);
            pthread_cond_destroy(&_cond);
        }
    };
}
