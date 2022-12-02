#include <sys/wait.h> /* wait */
#include <stdio.h>
#include <stdlib.h>   /* exit functions */
#include <unistd.h>   /* read, write, pipe, _exit */
#include <string.h>

extern long fun(long a, long b);
 
long recursion(long v[], int left, int right) {

    if (right - left < 1)
        return fun(v[left], v[right]);

    int middle = (left + right)/2;
    return fun(recursion(v, left, middle), recursion(v, middle+1, right));
}

int main() {
    // long x = 8;
    // long y = 4;
    // printf("%ld", fun(x, y));
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int number_count = 0;

    fp = fopen("./Practical_Q_1numbers.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        number_count ++;
//        printf("%s", line);
    }
    fclose(fp);
    fp = fopen("./Practical_Q_1numbers.txt", "r");

    printf("Number Counts: %d\n", number_count);

    long a[number_count];
    int counter = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        a[counter ++] = strtol(line, NULL, 10);
//        printf("%s", line);
    }


    int numProcess = 8;

    for (int childP = 0; childP < numProcess; childP++)
    {
        int child = fork();
        if (child < 0)
        {
            exit(EXIT_FAILURE);
        }
        if (child == 0)
        {
            // close(fd[0]);
            // int childSum = 0;
            // int start = childP * numPerProcess;
            // int stop = start + numPerProcess;
            printf("Child Process No [%d] PID [%d], PPID: : %d\n", childP, getpid(), getppid());
            // if (write(fd[1], &childSum, sizeof(childSum)) != sizeof(childSum))
            // {
            //     fprintf(stderr, "Child Process No [%d] PID [%d] failed to write to the pipe\n",
            //             childP, getpid());
            //     exit(EXIT_FAILURE);
            // }
            // close(fd[1]);
            exit(0);
        }
    }

    // long result = recursion(a, 0, number_count-1);
    
    // printf("%ld\n", result);
    sleep(5);
    fclose(fp);
    if (line)
        free(line);
}
