#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Nastya Gurskaya");
MODULE_DESCRIPTION("Calculator");
MODULE_VERSION("1");

#define PROC_FIRST "first"
#define PROC_SECOND "second"
#define PROC_OPERAND "operand"
#define DEV_RESULT "result"

#define PROC_MAX_SIZE 20

static struct proc_dir_entry *first_proc_file, *second_proc_file, *operand_proc_file;
static char first_buffer[PROC_MAX_SIZE], second_buffer[PROC_MAX_SIZE], operand_buffer[PROC_MAX_SIZE];
static unsigned long first_buffer_size = 0, second_buffer_size = 0, operand_buffer_size = 0;
static const int first_proc_index = 1, second_proc_index = 2, operand_proc_index = 3;

static ssize_t proc_write(struct file *filp, const char __user *buffer, size_t count, loff_t *data)
{
}
static ssize_t dev_read(struct file * file, char * buf, size_t count, loff_t *ppos)
{
}

static int calc_init(void)
{
    printk(KERN_INFO "Calc module started working\n");
    return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void calc_exit(void)
{
    	printk(KERN_INFO "Calc module stopped working\n");
	remove_proc_entry(PROC_FIRST, NULL);
	remove_proc_entry(PROC_SECOND, NULL);
	remove_proc_entry(PROC_OPERAND, NULL);
	misc_deregister(&result_dev);
}

module_init(calc_init);
module_exit(calc_exit);
