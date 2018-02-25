#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>	/*for put_user*/

int init_module(void);
void cleanup_module(void);

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "chardev"
#define BUF_LEN 80


static int Major;
static int Device_Open = 0;

static char msg[BUF_LEN];
static char *msg_ptr;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

int init_module(void){
	Major = register_chrdev(0, DEVICE_NAME, &fops);

	if (Major < 0){
		printk(KERN_INFO "Registering char device failed with %d\n", Major);
		return Major;
	}


}

