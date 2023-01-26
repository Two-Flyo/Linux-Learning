#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2] = {0};
    if (pipe(pipefd) != 0)
    {
        perror("pipe error");
        return 1;
    }

    // pipefd[0] 读取端
    // pipefd[1] 写入端
    printf("pipefd[0]:%d\n", pipefd[0]);
    printf("pipefd[1]:%d\n", pipefd[1]);
    // 我们让父进程读取,子进程写入
    if (fork() == 0)
    {
        // 子进程
        close(pipefd[0]);

        const char *msg = "hello world!";
        int count = 0;
        while (1)
        {
            write(pipefd[1], msg, strlen(msg));
            // sleep(1);
            // write(pipefd[1], "a", 1);
            // count++;
            // printf("count: %d\n", count);
            // break;
            
        }
        close(pipefd[1]);
        exit(0);
    }
    // 父进程 -- 读取
    close(pipefd[1]);
    while (1)
    {
        sleep(3);
        char c[64] = {0};
        ssize_t s = read(pipefd[0], c, sizeof(c));
        if(s > 0)
        {
            c[s] = 0;
            printf("father take: %s\n", c);
        }
        else if(s == 0)
        {
            printf("write quit...\n");
            break;
        }
        else
        {
            break;
        }

        break;

        // char buffer[64] = {0};
        // ssize_t s = read(pipefd[0], buffer, sizeof(buffer) - 1); // 如果read的返回值是0,意味着子进程关闭了文件描述符
        // if (s == 0)
        // {
        //     printf("child quit...\n");
        //     break;
        // }
        // else if (s > 0)
        // {
        //     buffer[s] = 0;
        //     printf("child say: %s\n", buffer);
        //     // 我们没有让父进程sleep
        // }
        // else
        // {
        //     printf("read error...\n");
        //     break;
        // }
    }
    close(pipefd[0]);
    int status =  0;
    waitpid(-1, &status, 0);
    printf("exit code: %d\n", (status >> 8) & 0xff);
    printf("exit signal: %d\n", status & 0x7f);
    return 0;
}

// pipefd[2] 是一个输出型参数,读取的两个打开的fd
