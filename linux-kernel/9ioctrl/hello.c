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
#include <linux/io.h>

#include "beep.h"


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

	
	if(size > strlen(kbuf))
	{
		size = strlen(kbuf);
	}

	if(copy_to_user(buf,kbuf, size))
	{
		error = -EFAULT;
		return error;
	}

	return size;
}
//write(fd,buff,40);
static ssize_t hello_write (struct file *filep, const char __user *buf, size_t size, loff_t *pos)
{
	int error;

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
	return size;
}

static int knum = 99;


/*

ioctl(fd,DEV_FIFO_GETVALUE, &num);
*/

long hello_ioctl (struct file *filep, unsigned int cmd, unsigned long arg)
{
	long err,ret;
	void __user *argp = (void __user *)arg;
	int __user *p = argp;


	if(_IOC_TYPE(cmd)!=DEV_FIFO_TYPE){
		pr_err("cmd   %u,bad magic 0x%x/0x%x.\n",cmd,_IOC_TYPE(cmd),DEV_FIFO_TYPE);
		return-ENOTTY;
	}
	if(_IOC_DIR(cmd)&_IOC_READ)
		ret=!access_ok(VERIFY_WRITE,(void __user*)arg,_IOC_SIZE(cmd));
	else if( _IOC_DIR(cmd)&_IOC_WRITE )
		ret=!access_ok(VERIFY_READ,(void   __user*)arg,_IOC_SIZE(cmd));

	if(ret){
		pr_err("bad   access %ld.\n",ret);
		return-EFAULT;
	}

	switch(cmd)
	{
		case DEV_FIFO_CLEAN:
			printk("DEV_FIFO_CLEAN\n");
			break;
		case DEV_FIFO_GETVALUE:
			err = put_user(knum, p);
			printk("DEV_FIFO_GETVALUE %d\n",knum);
			break;
		case DEV_FIFO_SETVALUE:
			err = get_user(knum, p);
			printk("DEV_FIFO_SETVALUE %d\n",knum);
			break;
		default:
			return -EINVAL;
			
	}
	return err;
}
static struct file_operations hello_ops = 
{
	.open = hello_open,
	.release = hello_release,
	.read = hello_read,
	.write = hello_write,
	.unlocked_ioctl = hello_ioctl,
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
