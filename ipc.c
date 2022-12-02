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

int min(int x, int y)
{
  return (x < y) ? x : y;
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
<<<<<<< HEAD
    int sizePerProcess = number_count / 8
    int fd[2];

    pipe(fd);

=======
    int sizePerProcess = number_count / 8;
>>>>>>> 8906e5cd6d1eea93161789724c0c57f2f88fe064

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
<<<<<<< HEAD
            int end = min(start + sizePerProcess - 1, number_count - 1)
            int pointers[2] = {start, end};

            // send the value on the write-descriptor.
            write(fd[1], &pointers, sizeof(pointers));
            printf("Parent(%d) Send Value: (%d, %d)\n", getpid(), pointers[0], pointers[1]);

            // close the write descriptor
            close(fd[1]);

        }
        else if (child == 0)
        {
            close(fd[1]);
            int pointers[2];
            read(fd[0], &pointers, sizeof(pointers));
            long result = recursion(a, pointers[0], pointers[1]);
            printf("Child Process No [%d], PID [%d], PPID: : [%d], \n", childP, getpid(), getppid());
            printf("Start: [%d], End: [%d], Result:[%ld]\n", pointers[0], pointers[1], result)
            close(fd[0]);
=======
            int end = min(start + sizePerProcess - 1, number_count - 1);
            long result = recursion(a, start, end);
            // int stop = start + numPerProcess;
            printf("Child Process No [%d], PID [%d], PPID: : [%d], \n", childP, getpid(), getppid());
            printf("Start: [%d], End: [%d], Result:[%ld]\n", start, end, result);
            // if (write(fd[1], &childSum, sizeof(childSum)) != sizeof(childSum))
            // {
            //     fprintf(stderr, "Child Process No [%d] PID [%d] failed to write to the pipe\n",
            //             childP, getpid());
            //     exit(EXIT_FAILURE);
            // }
            // close(fd[1]);
>>>>>>> 8906e5cd6d1eea93161789724c0c57f2f88fe064
            exit(0);
        }
    }

    // long result = recursion(a, 0, number_count-1);
    
    // printf("%ld\n", result);
    wait(NULL);
    // sleep(5);
    fclose(fp);
    if (line)
        free(line);
}
