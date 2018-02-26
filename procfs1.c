#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define procfs_name "helloworld"

struct proc_dir_entry *Our_Proc_File;

static int procfile_read (	char* buffer, 
					char ** buffer_location,
					off_t offset,
					int buffer_length, 
					int *eof,
					void *data){
	int ret;

	printk(KERN_INFO "procfile_read (/proc/%s) called\n", procfs_name);
	if (offset > 0){
		ret = 0;
	}
	else {
		ret = sprintf(buffer, "HelloWorld!\n");
	}

	return ret;
}

static int hello_proc_open(struct inode *inode, struct file *file){
	return 0;
}

static const struct file_operations hello_proc_fops = {
	.owner = THIS_MODULE,
	.open = hello_proc_open,
	.read = seq_read,
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
