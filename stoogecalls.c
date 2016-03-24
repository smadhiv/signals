#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/types.h>
#include <linux/sched.h>

SYSCALL_DEFINE1(goober, int, myarg){
	printk(KERN_ALERT "Hello from %d\n", myarg);
return(1);
}

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
	
