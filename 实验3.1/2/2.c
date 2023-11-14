#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        // Fork失败
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } else if (pid == 0) {
        // 子进程：执行ls命令
        printf("Child Process: executing 'ls'\n");
        execlp("/bin/ls", "ls", NULL);
        // 如果execlp返回，说明执行失败
        fprintf(stderr, "execlp Failed\n");
        exit(1);
    } else {
        // 父进程：等待子进程完成
        wait(NULL);
        printf("Child Process Complete\n");
    }

    return 0;
}
