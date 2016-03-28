#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define smunch(arg,sig) syscall(329,arg,sig) 
#define NUM_THREADS 2
 
/* create thread argument struct for thr_func() */
typedef struct _thread_data_t {
  int tid;
  double stuff;
} thread_data_t;
 
/* thread function */
void *thr_func(void *arg) {
  thread_data_t *data = (thread_data_t *)arg;
 smunch(getpid(), 10);
  printf("hello from thr_func, thread id: %d\n", data->tid);
 
  pthread_exit(NULL);
}

void *second(void * arg){
  thread_data_t *data = (thread_data_t *)arg;
  printf("I do not execute smunch \n");
  pthread_exit(NULL);
}

void *(*func[2])(void *arg);
int main(int argc, char **argv) {
  pthread_t thr[NUM_THREADS];
  int i, rc;
  func[0] = thr_func;
  func[1] = second;
  /* create a thread_data_t argument array */
  thread_data_t thr_data[NUM_THREADS];
 
  /* create threads */
  for (i = 0; i < NUM_THREADS; ++i) {
    thr_data[i].tid = i;
    if ((rc = pthread_create(&thr[i], NULL, func[i], &thr_data[i]))) {
      fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      return EXIT_FAILURE;
    }
  }
  /* block until all threads complete */
  for (i = 0; i < NUM_THREADS; ++i) {
    pthread_join(thr[i], NULL);
  }
 
  return EXIT_SUCCESS;
}
