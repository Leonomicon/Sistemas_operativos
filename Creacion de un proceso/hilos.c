#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error al ejecutar fork()");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        for (int i = 10000; i >= 1; i--) {
            printf("[Hijo  PID %d]: %d\n", getpid(), i);
        }
        exit(EXIT_SUCCESS);
    } else {
        for (int i = 1; i <= 10000; i++) {
            printf("[Padre PID %d]: %d\n", getpid(), i);
        }

        wait(NULL);
    }

    return EXIT_SUCCESS;
}
