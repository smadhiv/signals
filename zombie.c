#include <stdio.h>
#include<stdlib.h>
int main(){
	int pid, ret, i;
	switch(pid=fork()){
	case 0:
		printf("try to kill pid %d", getpid());
		exit(0);
		break;
	default:
		printf("without kiling %d\n", getpid());
		while(1){
		sleep(20);
		}
	}
return 0;
}
