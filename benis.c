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
#define MAX_LEN 255

char THICC = '=';		// Use - instead of = ?
unsigned int LENGTH;		// How long is the benis?
char BENIS[MAX_LEN];

static void create_benis(void)
{
	int i;
	BENIS[0] = '8';

	if (!LENGTH)
		LENGTH = 10;
	for(i = 1; i <= LENGTH; i++) {
		BENIS[i] = THICC;
	}
	BENIS[LENGTH+1] = 'D';
}

static int parse_input(const char* input, size_t len)
{
	return 0;
}

static ssize_t settings_write(struct file *file, const char __user *buf,
			   size_t len, loff_t *pos)
{
	/**
	 * Read user input for benis specs
	 * 0-253 0-1
	 */
	return parse_input(buf, len);
}

static ssize_t read_benis(struct file *file, char __user *buf, size_t len,
			  loff_t *pos)
{
	create_benis();
	raw_copy_to_user(buf, BENIS, LENGTH + 2);
	return LENGTH + 2;
}

static const struct file_operations dev_fops = {
	.owner	= THIS_MODULE,
	.llseek	= noop_llseek,
	.read	= read_benis,
	.write	= settings_write,
};

static struct miscdevice benisdev = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= DEV_NAME,
	.fops	= &dev_fops,
	.mode	= 0666
};

static int register_dev(void)
{
	int err = misc_register(&benisdev);
	if (err) {
		printk(KERN_INFO "Failed to erect %s!\n", MODULE_NAME);
		return -1;
	}
	printk(KERN_INFO "Erected %s.\n", MODULE_NAME);
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
