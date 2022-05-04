/*  
 *一口Linux
 *2021.6.21
 *version: 1.0.0
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "beep.h"

main()
{
	int fd;
	int len;

	int num;	

	int ret;
	
	fd = open("/dev/hellodev",O_RDWR);
	if(fd<0)
	{
		perror("open fail \n");
		return;
	}

	ioctl(fd,DEV_FIFO_CLEAN);

	
	ret = ioctl(fd,DEV_FIFO_GETVALUE,NULL);
	if(ret < 0)
	{
		perror("ioctl");
		return;
	}
	printf("num = %d \n",num);

	num = 77;
	ioctl(fd,DEV_FIFO_SETVALUE,&num);
	
	 
	close(fd);
}
