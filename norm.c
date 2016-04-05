#include<stdio.h>
#include<errno.h>
#include<sys/syscall.h>
#include<sys/signal.h>

#define deepsleep() syscall(328)
void sig1(){
  printf("\nSIGUSR1 works\n");
}

void sig2(){
 printf("\nSIGUSR2 works\n");
}

int main(){
  printf("goodnight, Irene?\n");
  signal(SIGUSR1, sig1);
  signal(SIGUSR2, sig2);
  deepsleep();
  printf("oops.. wokeup!\n");
  while(1){
    sleep(10);
  }
}

