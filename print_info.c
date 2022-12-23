#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/moduleparam.h>


int inp;
struct task_struct *task;
module_param(inp, int, 0644);

static int __init print_init(void){
    task = pid_task(find_vpid(inp), PIDTYPE_PID);
    printk(KERN_INFO "Installed module\n");
    printk(KERN_INFO "PID: %d\n", task->pid);
    printk(KERN_INFO "UID: %d\n",  task->cred->uid);
    printk(KERN_INFO "PGID: %d\n", task->group_leader->pid);
    printk(KERN_INFO "Command path: %s\n", task->comm);

    return 0;
}

static void __exit print_exit(void){
    printk(KERN_INFO "Removed module\n");
}

module_init(print_init);
module_exit(print_exit);

MODULE_LICENSE("GPL");