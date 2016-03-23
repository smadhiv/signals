#include <stdio.h>
#include <errno.h>
#include <sys/syscall.h>

#define goob(arg) syscall(325,arg)

int main(){
int ret;
ret = goob(5);
fprintf(stderr, "syscall returned %d\n");
return 0;
}
