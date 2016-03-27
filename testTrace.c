#include <stdio.h>
#include<unistd.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/signal.h>
#include <sys/ptrace.h>
#include <sys/wait.h>


#define sigcounter(arg) syscall(326,arg)
#define getcount(sig)  syscall(327,sig)
#define smunch(pid, sig) syscall(329, pid, sig)

void happy(){
	printf("\nExecuting happy function\n");
}

int main(){
	int pid, ret, i;
	switch(pid=fork()){
	case 0:
		printf("\nsriram");
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("/bin/sh", "sh", NULL);
		break;
	default:
		wait(NULL);
		ret = smunch(pid, 100);
		printf("\nsmunch returned %d\n", ret);
	}
return 0;
}
