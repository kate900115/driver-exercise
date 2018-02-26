#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>

#define procfs_name "helloworld"

struct proc_dir_entry *Our_Proc_File;

static int procfile_read (struct file * File, char __user* u, size_t size, loff_t* a){
/*	char buf[128];
	int i;
	for (i=0; i<128; i++){
		buf[i] = 0;
	}

	File = filp_open("~/zyuxuan/file_for_mod", O_RDONLY, 0);

	if (File==NULL){
		printk(KERN_INFO "File open error!\n");
	}
	else{
		printk(KERN_INFO "File open successful!\n");
	}
*/
	printk(KERN_INFO "procfile_read (/proc/%s) called\n", procfs_name);

	return 0;
}

static int hello_proc_open(struct inode *inode, struct file *file){
	printk(KERN_INFO "File has been successfully opened\n");
	return 0;
}

static const struct file_operations hello_proc_fops = {
	.owner = THIS_MODULE,
	.open = hello_proc_open,
	.read = procfile_read,
	.llseek = seq_lseek,
	.release = single_release,
};

int init_module(){
	Our_Proc_File = proc_create(procfs_name, 0644, NULL, &hello_proc_fops);

	if (Our_Proc_File == NULL){
		remove_proc_entry(procfs_name, NULL);
		printk(KERN_INFO "Error: Could not initialize /proc/%s\n", procfs_name);
		return -ENOMEM;
	}

	printk(KERN_INFO "/proc/%s created\n", procfs_name);
	return 0;
}


void cleanup_module(){
	remove_proc_entry(procfs_name, NULL);
	printk(KERN_INFO "/proc/%s removed\n", procfs_name);
}
