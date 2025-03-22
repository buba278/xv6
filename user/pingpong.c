// #include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"
#include <stddef.h>

// Note: Pipes should be shared between two processes
// Not designed for single source multiple consumer

int 
main(int argc, char *argv[])
{
  if(argc != 1) {
    fprintf(2, "usage: pingpong(void)\n");
    exit(1);
  }

  int fd1[2];
  pipe(fd1);
  
  // make two children
  int child1 = fork();

  if (child1 != 0) {
    // parent
    
    int fd2[2];
    pipe(fd2);

    int child2 = fork();
    if (child2 == 0) {
      // child 2
      char read_msg[5];
      while (!strcmp(read_msg, "ping\n")) {
        read(fd2[0], read_msg, sizeof(read_msg));
      }
      close(fd2[0]);
      fprintf(2, "%u: pong\n", getpid());

      char write_msg[] = "ACK";
      write(fd2[1], write_msg, sizeof(write_msg) + 1);
      close(fd2[1]);

      exit(0);
    }
    // once creating children as parent
    // wait for the two to exit
    char write_msg[] = "ping";
    write(fd1[1], write_msg, sizeof(write_msg) + 1);
    close(fd1[1]);
    write(fd2[1], write_msg, sizeof(write_msg) + 1);
    close(fd2[1]);
    char read_msg[4];
    // wait first ACK
    while (!strcmp(read_msg, "ACK\n")) {
      read(fd1[0], read_msg, sizeof(read_msg));
    }
    // second ACK
     while (!strcmp(read_msg, "ACK\n")) {
      read(fd2[0], read_msg, sizeof(read_msg));
    }
    close(fd1[0]);
    close(fd2[0]);
    int exit_pid = wait(NULL);
    if ((exit_pid == child1) |  (exit_pid == child2)) {
      exit_pid = wait(NULL);
      if ((exit_pid == child1) | (exit_pid == child2)) {
        exit(0);
      }
    }
    fprintf(2, "error: failed to ensure child process exits");
    exit(1);
  }
  else {
    // child 1
    char read_msg[5];
    while (!strcmp(read_msg, "ping\n")) {
      read(fd1[0], read_msg, sizeof(read_msg));
    }
    close(fd1[0]);
    fprintf(2, "%u: pong\n", getpid());
    char write_msg[] = "ACK";
    write(fd1[1], write_msg, sizeof(write_msg) + 1);
    close(fd1[1]);
  }
  exit(0);
}
