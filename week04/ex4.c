#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[], char *envp[]) {
    char inp[256];
    while (1) {
        fgets(inp, 256, stdin);
        
        char *cmd[16];
        for (int i = 0; i < 16; i++)
            cmd[i] = malloc(64*sizeof(char));

        int counter = 1;
        char *p = strtok(inp, " ");
        while (p != NULL) {
            strcpy(cmd[counter], p);
            p = strtok(NULL, " ");

            if (++counter >= 16) {
                break;
            }
        }

        // for (int i = 0; i < counter; i++)
        //     printf("%s|", cmd[i]);

        if (!strcmp(cmd[counter], "&")) {
            if (fork() == 0) {
                printf("[%d]\n", getpid());
                cmd[counter-1] = NULL;
                execve("/bin/sh", cmd, envp);
            }
        } else {
            cmd[counter+1] = NULL;
            execve("/bin/sh", cmd, envp);
        }

    }

    return 0;
}