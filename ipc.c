#include <sys/wait.h> /* wait */
#include <sys/stat.h>
#include <sys/fcntl.h>
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

int min(int x, int y)
{
  return (x < y) ? x : y;
}


int main() {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t readline;
    int numberCount = 0;


    fp = fopen("./Practical_Q_1numbers.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((readline = getline(&line, &len, fp)) != -1) {
        numberCount ++;
    }

    fclose(fp);

    fp = fopen("./Practical_Q_1numbers.txt", "r");

    printf("Number Counts: %d\n", numberCount);

    long a[numberCount];
    int counter = 0;

    while ((readline = getline(&line, &len, fp)) != -1) {
        a[counter ++] = strtol(line, NULL, 10);
    }

    fclose(fp);

    int numProcess = 32;
    int sizePerProcess = numberCount / numProcess + 1;

    char * myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    
    int fd[2];
    pipe(fd);

    for (int childP = 0; childP < numProcess; childP++)
    {
        int child = fork();
        if (child < 0)
        {
            exit(EXIT_FAILURE);
        }
        else if (child > 0)
        {   
            close(fd[0]);

            int start = childP * sizePerProcess;
            int end = min(start + sizePerProcess - 1, numberCount - 1);
            int pointers[2] = {start, end};

            write(fd[1], &pointers, sizeof(pointers));

            close(fd[1]);
        }
        else if (child == 0)
        {
            close(fd[1]);
            int pointers[2];
            read(fd[0], &pointers, sizeof(pointers));
            long result = recursion(a, pointers[0], pointers[1]);
            printf("Child Process No [%d], PID [%d], PPID: : [%d], \n", childP, getpid(), getppid());
            printf("Start: [%d], End: [%d], Result:[%ld]\n", pointers[0], pointers[1], result);
            close(fd[0]);
            int fifoFile = open(myfifo, O_WRONLY);
            write(fifoFile, &result, sizeof(result));
            close(fifoFile);
            exit(0);
        }
    }

    long subResults[numProcess];
    for (int i=0 ; i < numProcess; i++)
    {
        int fifoFile = open(myfifo, O_RDONLY);
        long result;
        read(fifoFile, &result, sizeof(result));
        subResults[i] = result;
        close(fifoFile);
    }

    wait(NULL);
    unlink(myfifo);
    sleep(5);

    long result;
    result = recursion(subResults, 0, numProcess-1);

    printf("THE FINAL RESULTS is:\n%ld\n", result);
    exit(0);
}
