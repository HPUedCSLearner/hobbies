/*  
 *一口Linux
 *2021.6.21
 *version: 1.0.0
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/wait.h> 
#include <linux/poll.h>

wait_queue_head_t rwq,wwq; 

int havedata = 0; // 0 empty  1 full

static int major = 237;
static int minor = 0;
static dev_t devno;
static struct cdev cdev;
struct device *class_dev = NULL;
struct class *cls;


static int hello_open (struct inode *inode, struct file *filep)
{
	printk("hello_open()\n");
	return 0;
}
static int hello_release (struct inode *inode, struct file *filep)
{
	printk("hello_release()\n");

	return 0;
}

#define KMAX_LEN 32
char kbuf[KMAX_LEN+1] = "kernel";


//read(fd,buff,40);

static ssize_t hello_read (struct file *filep, char __user *buf, size_t size, loff_t *pos)
{
	int error;

	wait_event_interruptible(rwq,havedata == 1);
	
	if(size > strlen(kbuf))
	{
		size = strlen(kbuf);
	}

	if(copy_to_user(buf,kbuf, size))
	{
		error = -EFAULT;
		return error;
	}
	havedata = 0;

	wake_up_interruptible(&wwq);
	
	return size;
}
//write(fd,buff,40);
static ssize_t hello_write (struct file *filep, const char __user *buf, size_t size, loff_t *pos)
{
	int error;
	
	wait_event_interruptible(wwq,havedata == 0);
	
	if(size > KMAX_LEN)
	{
		size = KMAX_LEN;
	}
	memset(kbuf,0,sizeof(kbuf));
	if(copy_from_user(kbuf, buf, size))
	{
		error = -EFAULT;
		return error;
	}
	printk("%s\n",kbuf);

	havedata = 1;
	wake_up_interruptible(&rwq);
	return size;
}

unsigned int hello_poll(struct file *file, struct poll_table_struct *ptable)
{
	unsigned mask = 0;

	poll_wait(file, &rwq, ptable);
	poll_wait(file, &wwq, ptable);

	if(havedata == 1)
	{
		mask |= POLLIN; //can read
	}
	if(havedata == 0)
	{
		mask |= POLLOUT; //can write
	}
	return mask;
}


static struct file_operations hello_ops = 
{
	.open = hello_open,
	.release = hello_release,
	.read = hello_read,
	.write = hello_write,
	.poll = hello_poll,
};
static int hello_init(void)
{
	int result;
	int error;
	
	printk("hello_init \n");
	result = register_chrdev( major, "hello", &hello_ops);
	if(result < 0)
	{
		printk("register_chrdev fail \n");
		return result;
	}
	cls = class_create(THIS_MODULE, "hellocls");
	if (IS_ERR(cls)) {
		printk(KERN_ERR "class_create() failed for cls\n");
		result = PTR_ERR(cls);
		goto out_err_1;
	}
	devno = MKDEV(major, minor);
	
	class_dev = device_create(cls, NULL, devno, NULL, "hellodev");
	if (IS_ERR(class_dev)) {
		result = PTR_ERR(class_dev);
		goto out_err_2;
	}


	init_waitqueue_head(&rwq); 
	init_waitqueue_head(&wwq); 
	return 0;

out_err_2:
	class_destroy(cls);
out_err_1:
	unregister_chrdev(major,"hello");
	return 	result;
}
static void hello_exit(void)
{
	printk("hello_exit \n");
	device_destroy(cls, devno);
	class_destroy(cls);
	unregister_chrdev(major,"hello");
	return;
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
//proc/devices
