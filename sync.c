#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/spinlock.h>

#define TAG "week9" 

static struct task_struct *t1;
static struct task_struct *t2;
static struct task_struct *t3;
static struct task_struct *t4;
static struct task_struct *t5;

DEFINE_SPINLOCK(lock);

static int counter = 0;

static int threadMethod(void *unused) {
    int i = 0;

    for (i=0; i<5; i++) {
        counter++;
        spin_lock(&lock);
        printk(KERN_INFO "I'm %s, counter: %d", current->comm, counter);
        spin_unlock(&lock);
        msleep(100);
    }
  
    return 0;
}

void createThreads(void) {
    t1 = kthread_run(threadMethod, NULL, "mythread1");
    t2 = kthread_run(threadMethod, NULL, "mythread2");
    t3 = kthread_run(threadMethod, NULL, "mythread3");
    t4 = kthread_run(threadMethod, NULL, "mythread4");
    t5 = kthread_run(threadMethod, NULL, "mythread5");

}

int init_module(void)
{
    printk(KERN_INFO "START %s\n", TAG);  
    createThreads();
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "END %s\n", TAG);
}