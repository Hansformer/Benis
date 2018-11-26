#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#ifndef MODULE_NAME
#define MODULE_NAME "Benis"
#endif

#define DEV_NAME "benis"

static ssize_t settings_write(struct file *file, const char __user *buf,
			   size_t len, loff_t *pos)
{
	return 0;
}

static ssize_t read_benis(struct file *file, char __user *buf, size_t len,
			  loff_t *pos)
{
	char *benis = "8=====D\n";
	raw_copy_to_user(buf, benis, 8);
	return 8;
}

static const struct file_operations dev_fops = {
	.owner = THIS_MODULE,
	.llseek = noop_llseek,
	.read = read_benis,
	.write = settings_write,
};

static struct miscdevice benisdev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEV_NAME,
	.fops = &dev_fops,
	.mode = 0666
};

static int register_dev(void)
{
	int err = misc_register(&benisdev);
	if (err) {
		printk(KERN_INFO "Failed to erect %s!\n", MODULE_NAME);
		return -1;
	}
	printk(KERN_INFO "Erected %s. \n", MODULE_NAME);
	return 0;
}

static int __init erect(void)
{
	return register_dev();
}

static void __exit eject(void)
{
	misc_deregister(&benisdev);
	printk(KERN_INFO "%s has been ejected!\n", MODULE_NAME);
}

module_init(erect);
module_exit(eject);

MODULE_LICENSE("Dual MIT/GPL");
