#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/signal.h>
#include <unistd.h>
#define sigcounter(arg) syscall(326,arg)
#define getcount(sig)  syscall(327,sig)

void happy(){
	printf("\nExecuting happy function\n");
}

int main(){
	int pid, ret, i, parent;
	switch(pid=fork()){
	case 0:
		parent = getpid();
		printf("\n PID is %u", parent);
		signal(SIGUSR1, happy);
		do{
		getcount(SIGUSR1);
		sleep(5);
		}while(1);
		break;
	default:
		parent = getpid();
		printf("\nSource PID is %u", parent);
		ret = sigcounter(pid);
		while(1){
		sleep(5);
		ret = kill(pid, SIGUSR1);
		}
	}
return 0;
}
