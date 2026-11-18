#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: childcreates <iterations>\n");
        exit(1);
    }

    int iterations = strtol(argv[1], NULL, 10);

    for (int i = 0; i < iterations; i++) {
        int n = fork();
        if (n < 0) {
            perror("fork");
            exit(1);
        }
        if (n > 0) {
            // Only the child continues to the next iteration.
            while (waitpid(n, NULL, 0) < 0) {
                if (errno != EINTR) {
                    perror("waitpid");
                    return 1;
                }
            }
            return 0;
        }
        printf("ppid = %d, pid = %d, i = %d\n", getppid(), getpid(), i);
        // Flush before the next fork, including when stdout is redirected.
        fflush(stdout);
    }

    return 0;
}
