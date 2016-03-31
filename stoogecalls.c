#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/wait.h>

// Test syscall that does nothing
SYSCALL_DEFINE1(goober, int, myarg){
	printk(KERN_ALERT "Hello from %d\n", myarg);
return(1);
}

// Initialize count for each signal under a process
SYSCALL_DEFINE1(init_sigcounter, pid_t, pid){
	unsigned long flags;
	int i;
	struct task_struct *p;
	p = pid_task(find_vpid(pid), PIDTYPE_PID);
	lock_task_sighand(p, &flags);
	for(i = 0; i < 64; i++){
	p->sighand->sigcounter[i] = 0;
	}
	unlock_task_sighand(p, &flags);
	return(1);
}

// Return count of each signal under a process
SYSCALL_DEFINE1(get_sigcounter, int, signumber){
	unsigned long flags;
	struct task_struct *p;
	pid_t pid = current->pid;
	p = pid_task(find_vpid(pid), PIDTYPE_PID);
	lock_task_sighand(p, &flags);
	pr_alert("%d\n", p->sighand->sigcounter[signumber]);
	unlock_task_sighand(p, &flags);
	return(1);
}

// Deep-sleeper
__sched sleep_on(wait_queue_head_t *q){
  unsigned long flags;
  wait_queue_t wait;

  init_waitqueue_entry(&wait, current);
  __set_current_state(TASK_UNINTERRUPTIBLE);
  spin_lock_irqsave(&q->lock, flags);
  __add_wait_queue(q, &wait);
  spin_unlock(&q->lock);
  schedule();
  spin_lock_irq(&q->lock);
  __remove_wait_queue(q, &wait);
  spin_unlock_irqrestore(&q->lock, flags);
  return;
}

DECLARE_WAIT_QUEUE_HEAD(gone);
SYSCALL_DEFINE0(deepsleep){
  sleep_on(&gone);
}

SYSCALL_DEFINE2(smunch, pid_t,pid, long, bit_pattern){
//Check if multi threaded
  struct task_struct *p;
  bool ret;
  p = pid_task(find_vpid(pid), PIDTYPE_PID);
  ret = current_is_single_threaded();
  if(ret == false){
    pr_alert("\nError : Multithreaded process, cannot proceed\n");
    return -1;
  }
  
//Check if traced
  if(p->ptrace & PT_PTRACED){
    pr_alert("\nError : Traced process, cannot proceed\n");
    return -1;
  }

//Check if zombie state 
  if(p->exit_state == EXIT_ZOMBIE){
    pr_alert("\nIn zombie state\n");
  }

//Check if in task inunterruptible state
  if(p->state == TASK_UNINTERRUPTIBLE){
    pr_alert("\nIn uninterrruptible state\n");
  }
  release_task(p);
return 0;
}
