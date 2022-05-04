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
#include <linux/slab.h>
#include <linux/uaccess.h>
static int major = 237;
static int minor = 0;
static dev_t devno;

#define MAX_COM_NUM 2

struct mydev{
	struct cdev cdev;
	char *reg;
	int test;
};
struct mydev *pmydev[MAX_COM_NUM];

ssize_t dev_fifo_read (struct file *file, char __user *buf, size_t size, loff_t *pos)
{
	struct mydev *cd;

	cd = (struct mydev *)file->private_data;
	printk("read()       file->private_data         cd->test=%d\n",cd->test);

	if(copy_to_user(buf, &minor, size)){
		return -EFAULT;
	}

	return size;
}
int dev_fifo_close (struct inode *inode, struct file *file)
{
	printk("dev_fifo_close()\n");
	return 0;
}
static int dev_fifo_open (struct inode *inode, struct file *file)
{
	struct mydev *cd;

	cd = container_of(inode->i_cdev, struct mydev, cdev);
	file->private_data = cd;
	return 0;
}
static struct file_operations dev_fifo_ops = 
{
	.open = dev_fifo_open,
	.read = dev_fifo_read,
	.release = dev_fifo_close,
};
static int dev_fifo_init(void)
{
	int result;
	int error;
	int i = 0;

	printk("dev_fifo_init \n");
	devno = MKDEV(major,minor);  
	result = register_chrdev_region(devno, MAX_COM_NUM, "test");
	if(result<0)
	{
		printk("register_chrdev_region fail \n");
		goto ERR1;
	}


	for(i=0;i<MAX_COM_NUM;i++)
	{
		pmydev[i] =kmalloc(sizeof(struct mydev), GFP_KERNEL);
	}

	for(i=0;i<MAX_COM_NUM;i++)
	{
		pmydev[i]->test = i; 
		cdev_init(&pmydev[i]->cdev,&dev_fifo_ops);
		devno = MKDEV(major,i);    
		error = cdev_add(&pmydev[i]->cdev,devno,1);
		if(error < 0)
		{
			printk("cdev_add fail \n");
			goto ERR2;
		}
	}
	return 0;
ERR2:
	devno = MKDEV(major,0);  
	unregister_chrdev_region(devno,MAX_COM_NUM);
	for(i=0;i<MAX_COM_NUM;i++)
	{
		kfree(pmydev[i]);
	}
	return error;
ERR1:
	return result;
}
static void dev_fifo_exit(void)
{
	int i;

	printk("dev_fifo_exit \n");

	for(i=0;i<MAX_COM_NUM;i++)
	{
		cdev_del(&pmydev[i]->cdev);
	}
	for(i=0;i<MAX_COM_NUM;i++)
	{
		kfree(pmydev[i]);
	}
	devno = MKDEV(major,0);  
	unregister_chrdev_region(devno,MAX_COM_NUM);
	return;
}
MODULE_LICENSE("GPL");
MODULE_AUTHOR("daniel.peng");
module_init(dev_fifo_init);
module_exit(dev_fifo_exit);

