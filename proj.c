#include<stdio.h>
#include<errno.h>
#include<sys/syscall.h>
#include<string.h>

#define smunch(arg, sig) syscall(329, arg, sig)

int main(int argc, char **argv){
  int pid;
  long sig;
  pid = atoi(argv[1]);
  sig = atol(argv[2]);
  smunch(pid, sig);
  return 0;
}

