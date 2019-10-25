#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int i;
    int iterations;
    pid_t n;

    if (argc != 2) {
        fprintf(stderr, "Usage: parentcreates <iterations>\n");
        exit(1);
    }

    iterations = strtol(argv[1], NULL, 10);

    for (i = 0; i < iterations; i++) {
        n = fork();
        if (n < 0) {
            perror("fork");
            exit(1);
        } else if (n == 0) {
	        printf("ppid = %d, pid = %d, i = %d\n", getppid(), getpid(), i);
	        exit(1);
        } else if (i == 0 && n > 0) {
	        printf("ppid = %d, pid = %d, i = %d\n", getppid(), getpid(), i);
	    }
    }

    for (i = 0; i < iterations; i++) {
	    int status;
        wait(&status);
    }

    return 0;
}