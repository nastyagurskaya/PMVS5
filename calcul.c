#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Calculator");
MODULE_AUTHOR("Nastya Gurskaya");
MODULE_VERSION("1");

#define BUF_LEN 80

static ssize_t dev_first_write(struct file *filp, const char *buffer, size_t length, loff_t *offset);

static ssize_t dev_second_write(struct file *filp, const char *buffer, size_t length, loff_t *offset);

static ssize_t dev_operator_write(struct file *filp, const char *buffer, size_t length, loff_t *offset);

static int first_dev_file, second_dev_file, operand_dev_file;
static struct proc_dir_entry *proc_result;
static char result[BUF_LEN];
static char first[BUF_LEN];
static char second[BUF_LEN];
static char operand[BUF_LEN];

static ssize_t dev_first_write(struct file *filp, const char *buff, size_t len, loff_t *off) {
    if (copy_from_user(first, buff, len)) {
        return -EFAULT;
    }
    return len;
}

static ssize_t dev_second_write(struct file *filp, const char *buff, size_t len, loff_t *off) {
    if (copy_from_user(second, buff, len)) {
        return -EFAULT;
    }
    return len;
}

static ssize_t dev_operator_write(struct file *filp, const char *buff, size_t len, loff_t *off) {
    if (copy_from_user(operand, buff, len)) {
        return -EFAULT;
    }
    return len;
}

static ssize_t proc_read(struct file *filp, char *buffer, size_t length,loff_t *offset) {
    ssize_t cnt;
    ssize_t ret;
    int nfirst;
    int nsecond;
    int nresult;
    sscanf(first, "%d", &nfirst);
    sscanf(second, "%d", &nsecond);
    if (operand[0] == 'm') {
        nresult = nfirst * nsecond;
        sprintf(result, "%d", nresult);
    }
    else if (operand[0] == '-') {
        nresult = nfirst - nsecond;
        sprintf(result, "%d", nresult);
    }
    else if (operand[0] == '+') {
        nresult = nfirst + nsecond;
        sprintf(result, "%d", nresult);
    }
    else if (operand[0] == '/' && nsecond != 0) {
        nresult = nfirst / nsecond;
        sprintf(result, "%d", nresult);
    }
    else {
        sprintf(result, "NaN");
    }
    cnt = strlen(result);
    ret = copy_to_user(buffer, result, cnt);
    *offset += cnt - ret;
    if (*offset > cnt)
        return 0;
    else
        return cnt;
}

static struct file_operations fops = {
        .owner = THIS_MODULE,
        .read = proc_read
};

static struct file_operations dev_first_fops = {
        .owner = THIS_MODULE,
        .write = dev_first_write,
};

static struct file_operations dev_second_fops = {
        .owner = THIS_MODULE,
        .write = dev_second_write
};

static struct file_operations dev_operator_fops = {
        .owner = THIS_MODULE,
        .write = dev_operator_write
};
static int calc_init(void)
{		
	printk(KERN_INFO "Calc module started working\n");
	first_dev_file =register_chrdev(0, "first", &dev_first_fops);
    	if (first_dev_file < 0) {
        	printk(KERN_ALERT"Registering char device failed with %d\n", first_dev_file);
        return first_dev_file;
    	}
	second_dev_file = register_chrdev(0, "second", &dev_second_fops);
    if (second_dev_file < 0) {
        printk(KERN_ALERT
        "Registering char device failed with %d\n", second_dev_file);
        return second_dev_file;
    }
	operand_dev_file = register_chrdev(0, "operator", &dev_operator_fops);
    if (operand_dev_file < 0) {
        printk(KERN_ALERT
        "Registering char device failed with %d\n", operand_dev_file);
        return operand_dev_file;
    }
	proc_result = proc_create("result", 0, NULL, &fops);
    if (proc_result == NULL) {
        printk(KERN_ALERT
        "Creating proc failed\n");
        return -1;
    }
    return 0;
}

static void calc_exit(void)
{
    unregister_chrdev(first_dev_file, "first");
    unregister_chrdev(second_dev_file, "second");
    unregister_chrdev(operand_dev_file, "operator");
    remove_proc_entry("result", NULL);
}


module_init(calc_init);
module_exit(calc_exit);
