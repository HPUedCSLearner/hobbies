/*
*公众号 ：一口Linux
*2021.6.26
*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>


int hello_probe(struct platform_device *pdev)
{
	printk("match ok\n");

	printk("mem = %x \n",pdev->resource[0].start);
	printk("irq = %d \n",pdev->resource[1].start);

	//ioremap
	//request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags, const char * name, void * dev)
	
	return 0;
}
int hello_remove(struct platform_device *pdev)
{
	printk("hello_remove\n");
	return 0 ;
}




struct platform_driver hello_driver = {
	.probe = hello_probe,
	.remove = hello_remove,
	.driver.name = "yikoulinux",
};



static int hello_init(void)
{
	printk("hello_init\n");
	return platform_driver_register(&hello_driver);
}

static void hello_exit(void)
{
	printk("hello_exit\n");
	platform_driver_unregister(&hello_driver);
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
