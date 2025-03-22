#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){ 
    fprintf(2, "usage: sleep time (int seconds)\n");
    exit(1); // exit with failure status
  }
  
  //dont use sleep system call
  int init_time = uptime();

  // take pointer of time_t to store seconds
  while ((uptime() - init_time) < atoi(argv[1])) {}
  
  exit(0);
}

