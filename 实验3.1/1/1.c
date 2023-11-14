#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        // Fork失败
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } else if (pid == 0) {
        // 子进程
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        int exitValue;
        printf("Enter exit value for child process: ");
        scanf("%d", &exitValue);
        printf("Child Process exiting...\n");
        exit(exitValue);
    } else {
        // 父进程
        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);
        waitpid(pid, &status, 0); // 等待子进程退出
        printf("Child process exited with status %d\n", WEXITSTATUS(status));
        printf("Parent Process exiting...\n");
    }

    return 0;
}