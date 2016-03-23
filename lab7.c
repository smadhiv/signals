#include <stdio.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/signal.h>

#define sigcounter(arg) syscall(326,arg)
#define getcount(sig)  syscall(327,sig)

void happy(){
	printf("Executing happy function\n");
}

int main(){
	int pid, ret, i;
	switch(pid=fork()){
	case 0:
		signal(SIGUSR1, happy);
		do{
		getcount(SIGUSR1);
		getcount(SIGSTOP);
		getcount(SIGCONT);
		getcount(SIGWINCH);
		getcount(SIGURG);
		sleep(10);
		}while(1);
		break;
	default:
		ret = sigcounter(pid);
		while(1){
		sleep(10);
		ret = kill(pid, SIGUSR1);
		ret = kill(pid, SIGSTOP);
		ret = kill(pid, SIGCONT);
		ret = kill(pid, SIGWINCH);
		ret = kill(pid, SIGURG);
		}
	}
return 0;
}
