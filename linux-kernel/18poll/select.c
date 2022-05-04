/*  
 *一口Linux
 *2021.6.21
 *version: 1.0.0
*/

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#if 0
void FD_CLR(int fd, fd_set *set);   从集合set 删除fd
int  FD_ISSET(int fd, fd_set *set);   判断fd是不是在集合中？
void FD_SET(int fd, fd_set *set);    将fd加入到set中
void FD_ZERO(fd_set *set);           清空set
#endif

void main(void)
{
	int fd;
	int max_fd;
	fd_set readfd;
	fd_set writefd;


	fd = open("/dev/hellodev",O_RDWR);
	if(fd<0)
	{
		perror("open fail \n");
		return;
	}

	//while(1)
	{
		FD_ZERO(&readfd);
		FD_ZERO(&writefd);
		FD_SET(fd,&readfd);
		FD_SET(fd,&writefd);

		select(fd+1,&readfd,&writefd,NULL,NULL);
		if(FD_ISSET(fd,&readfd))
		{
			//can read
			printf("can read\n");
			
		}
		if(FD_ISSET(fd,&writefd))
		{
			//can write
			printf("can write\n");
		}
		sleep(1);
	}
}
