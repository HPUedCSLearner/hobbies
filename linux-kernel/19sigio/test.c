/*  
 *公众号：一口Linux
 *2021.6.21
 *version: 1.0.0
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<signal.h>

char buff[64] = {0};
int fd;

void func(int signo)
{
	printf("signo= %d\n",signo);
	read(fd,buff,sizeof(buff));
	printf("buff=%s\n",buff);
	return ;
}

main()
{

	int flage;

	fd = open("/dev/hellodev",O_RDWR);
	if(fd<0)
	{
		perror("open fail \n");
		return;
	}

	fcntl(fd,F_SETOWN,getpid());
	flage=fcntl(fd,F_GETFL);
	fcntl(fd,F_SETFL,flage|FASYNC);
    signal(SIGIO,func);
	while(1);
	 
	close(fd);
}