#include "kernel/types.h"
#include "user/user.h"
#include <stddef.h>

// filter primes based on filter stages that remove multiples from the latest lowest prime then pass to new pipe with new filter
// this process is concurrent like a pipeline

// Note: consider pipe transfer limit (primes 40 seems to be limit)
// no ACK needed? still works? ASK TALIA

int main(int argc, char *argv[]) 
{
    int limit = atoi(argv[1]);
    if (argc != 2 || limit > 200) {
        fprintf(2,"error: usage primes(int num <= 200)\n");
        exit(1);
    }

    // base set of numbers: 2 -> limit
    int nums[limit - 1]; // not including 1
    for(int i = 0; i < limit - 1; i++) {
        nums[i] = i + 2;
    }

    int fd[2];
    pipe(fd);

    // start of filtering process 
    if (fork() == 0) {
        // child process
        close(fd[1]);
        while (1) {
            int length;
            // break rather than leave it be (robust)
            // was overflowing before with pipes not properly closing
            if (read(fd[0], &length, sizeof(length)) <= 0) break;

            int divisor;
            if (read(fd[0], &divisor, sizeof(divisor)) <= 0) break;
            fprintf(2, "%d\n", divisor);

            int filtered_nums[length];
            int free_index = 0;

            for (int i = 0; i < length; i++) {
                int num;
                if (read(fd[0], &num, sizeof(num)) <= 0) break;

                if (num % divisor != 0) {
                    filtered_nums[free_index++] = num;
                }
            }

            close(fd[0]);

            if (free_index == 0) break;

            int filter_fdd[2];
            pipe(filter_fdd);

            if (fork() == 0) {
                close(filter_fdd[1]);
                fd[0] = filter_fdd[0];
                // DONT CLOSE PIPE HERE!
                // OTHERWISE your copy into fd[0] also closes
                // Pipe address matters not instance holding it
                continue;
            } else {
                close(filter_fdd[0]);
                // think of this line as: writing to new instance of fd (line 62)
                // just no context switch as this process is halted (done)
                write(filter_fdd[1], &free_index, sizeof(free_index));
                // pipe through entire array at once
                write(filter_fdd[1], &filtered_nums[0], free_index * sizeof(int));
                close(filter_fdd[1]);
                // prevent orphan case
                wait(NULL);
                break;
            }
        }
        exit(0);
    } 
    // parent
    else {
        close(fd[0]);

        int length = limit - 1;
        write(fd[1], &length, sizeof(length));
        write(fd[1], &nums[0], length * sizeof(int));

        close(fd[1]);
        // prevent orphan case
        wait(NULL);
    }
    exit(0);
}