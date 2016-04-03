#include<stdio.h>
#include<errno.h>
#include<sys/syscall.h>
#include<sys/signal.h>

#define deepsleep() syscall(328)
void happy(){
  printf("\nim happy \n");
}

int main(){
  printf("goodnight, Irene?\n");
  signal(SIGUSR1, happy);
  printf("oops.. wokeup!\n");
  while(1){
    sleep(1);
  }
}


