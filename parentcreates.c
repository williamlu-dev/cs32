#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: parentcreates <iterations>\n");
        exit(1);
    }

    int iterations = strtol(argv[1], NULL, 10);

    int children = 0;
    int result = 0;
    for (int i = 0; i < iterations; i++) {
        int n = fork();
        if (n < 0) {
            perror("fork");
            result = 1;
            break;
        }
        if (n == 0) {
            printf("ppid = %d, pid = %d, i = %d\n", getppid(), getpid(), i);
            return 0;
        }
        children++;
    }

    // Reap the children after the original parent has finished creating them.
    while (children > 0) {
        if (wait(NULL) >= 0) {
            children--;
        } else if (errno != EINTR) {
            perror("wait");
            return 1;
        }
    }

    return result;
}
