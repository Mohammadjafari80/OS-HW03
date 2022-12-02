#include <sys/wait.h> /* wait */
#include <stdio.h>
#include <stdlib.h>   /* exit functions */
#include <unistd.h>   /* read, write, pipe, _exit */
#include <string.h>

extern long fun(long a, long b);
 
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
        a[number_count ++] = strtol(line, NULL, 10);;;
//        printf("%s", line);
    }

    printf("%ld\n", a[0])
    
    fclose(fp);
    if (line)
        free(line);
}
