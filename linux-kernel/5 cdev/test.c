/*  
 *一口Linux
 *2021.6.21
 *version: 1.0.0
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
main()
{
	int fd;
	fd = open("/dev/test",O_RDWR);
	if(fd<0)
	{
		perror("open fail \n");
		return;
	}
	printf("open ok \n ");
}
