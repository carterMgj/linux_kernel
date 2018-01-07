#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/sched.h>
/*
 *  *  * Jumper probe for do_fork.
 *   *   * Mirror principle enables access to arguments of the probed routine
 *    *    * from the probe handler.
 *     *     */

/* Proxy routine having the same arguments as actual do_fork() routine */




static long jdo_execve(char * filename,
                        char __user *__user *argv,
                        char __user *__user *envp,
                        struct pt_regs * regs)
{
    struct task_struct *task = current;
    printk("command: %s\nargv: ",filename);
    int i;
    for(i = 1; ; i++)
    {
        if(argv[i])
        {
            printk("%s ", argv[i]);
        }
        else break;
    }
    printk("\nprocess tree:\n");
    while(1)
    {
        if(task->pid == 0){
            printk("%s(%d)\n", task->comm, task->pid);
            break;
        }
        printk("%s(%d)->", task->comm, task->pid);
        task = task->parent;
    }
    printk("\n");
    /* Always end with a call to jprobe_return(). */
    jprobe_return();
    return 0;
}

static struct jprobe my_jprobe = {
    .entry            = jdo_execve,
    .kp = {
        .symbol_name    = "sys_execve",
    },
};

static int __init jprobe_init(void)
{
    int ret;
    printk(KERN_ALERT "Hello,guy\n");
    ret = register_jprobe(&my_jprobe);
    if (ret < 0) {
        printk(KERN_ALERT "register_jprobe failed, returned %d\n", ret);
        return -1;
    }
    printk(KERN_ALERT "Planted jprobe at %p, handler addr %p\n",
           my_jprobe.kp.addr, my_jprobe.entry);
    return 0;
}

static void __exit jprobe_exit(void)
{
    unregister_jprobe(&my_jprobe);
    printk(KERN_ALERT "jprobe at %p unregistered\n", my_jprobe.kp.addr);
}

module_init(jprobe_init)
module_exit(jprobe_exit)
MODULE_LICENSE("GPL");
