#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[], char *envp[]) {
    char inp[256];
    
    printf(">> ");
    fgets(inp, 256, stdin);
    inp[strlen(inp)-1] = 0; // remove '\n' at the end
    
    char *cmd[16]; // array of arguments
    for (int i = 0; i < 16; i++)
        cmd[i] = malloc(64*sizeof(char));

    // tokenize the input
    int counter = 1;
    cmd[0] = strtok(inp, " ");
    while (cmd[counter-1] != NULL) {
        cmd[counter] = strtok(NULL, " ");

        if (++counter >= 16) {
            break;
        }
    }
    counter--;

    if (!strcmp(cmd[counter-1], "&")) {
        if (fork() == 0) {
            printf("[%d]\n", getpid());
            cmd[counter-1] = NULL;
            execvp(cmd[0], cmd);
            exit(0);
        } else {
          sleep(1);
        }
    } else {
        cmd[counter] = NULL;
        execvp(cmd[0], cmd);
    }
    


    return 0;
}
