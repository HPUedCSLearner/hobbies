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
  int fd0,fd1;
  int minor;
  
  fd0 = open("/dev/com0",O_RDWR);
  if(fd0<0)
  {
    perror("open fail \n");
    return;
  }
  printf("open /dev/com0 OK\n");

  read(fd0,&minor,sizeof(minor));
  printf("minor of /dev/com0 =%d\n",minor);
  close(fd0);
  
  fd1 = open("/dev/com1",O_RDWR);
  if(fd1<0)
  {
    perror("open fail \n");
    return;
  }
  printf("open /dev/com1 OK\n");

  read(fd1,&minor,sizeof(minor));
  printf("minor of /dev/com1 =%d\n",minor);
  close(fd1);
}
