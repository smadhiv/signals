#include <stdio.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/signal.h>

#define sigcounter(arg) syscall(326,arg)
#define getcount(sig)  syscall(327,sig)

void happy(){
	printf("\nExecuting happy function\n");
}

int main(){
	int pid, ret, i;
	switch(pid=fork()){
	case 0:
		signal(SIGUSR1, happy);
		do{
		getcount(SIGUSR1);
		sleep(10);
		}while(1);
		break;
	default:
		ret = sigcounter(pid);
		printf("\nSource PID is %u", getpid());
		while(1){
		sleep(10);
		ret = kill(pid, SIGUSR1);
		}
	}
return 0;
}
