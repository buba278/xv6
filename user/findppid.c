#include "kernel/types.h"
#include "user/user.h"
#include <stddef.h>

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(2,"error: usage findppid(int processes)\n");
        exit(1);
    }

    // think about how memory will be copied on write
    int child_count = 0;

    // spawn n number of child processes
    while (child_count != atoi(argv[1])) {
        int pid = fork();
        child_count++;

        // lock parent
        if (pid != 0) {
            wait(NULL);
            // essentially: this process is done
            child_count = atoi(argv[1]);
            // break out of loop - child is done
        }
        // last child # argv[1] will satisfy while()
    }

    // prints then frees previous parent 
    fprintf(2, "my ID is %u, my parent ID is %u\n", getpid(), getppid());
    exit(0);
}
