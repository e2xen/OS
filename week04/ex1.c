#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t n;
    
    switch (n = fork()) {
        case -1:
            printf("failed to create a process\n");
            exit(1);

        case 0:
            printf("Hello from child [PID - %d]\n", getpid());
            break;

        default:
            printf("Hello from parent [PID - %d]\n", getpid());
            break;
    }

    return (0);
}

/*
    Output:
    Hello from parent [PID - 40880]
    Hello from child [PID - 40881]
    Hello from parent [PID - 40882]
    Hello from child [PID - 40883]
    Hello from parent [PID - 40884]
    Hello from child [PID - 40885]
    Hello from parent [PID - 40886]
    Hello from child [PID - 40887]
    Hello from parent [PID - 40888]
    Hello from child [PID - 40889]
    Hello from parent [PID - 40890]
    Hello from child [PID - 40891]
    Hello from parent [PID - 40892]
    Hello from child [PID - 40893]
    Hello from parent [PID - 40894]
    Hello from child [PID - 40895]
    Hello from parent [PID - 40896]
    Hello from child [PID - 40897]
    Hello from parent [PID - 40898]
    Hello from child [PID - 40899]

    Each of 10 times a parent process creates a child process, which takes control over the processor after the parent process
*/
