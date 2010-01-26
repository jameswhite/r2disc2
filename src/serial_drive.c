#include <stdio.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h> 

int open_port(void) {
  int fd; /* File descriptor for the port */
  fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
   /*
    * Could not open the port.
    */
    perror("open_port: Unable to open /dev/ttyS0 - ");
  }
  else
    fcntl(fd, F_SETFL, 0);
  return (fd);
}

int main(){
    unsigned short x;
    int fd, n, m, o;
    char buf[255];

    printf("Connecting to /dev/ttyS0\nIf this hangs power cycle the amtren device\n");
    fd=open_port();
    o = write(fd, "C", 1);
    if (n < 0) fputs("write() of 1 byte failed!\n", stderr);
    fcntl(fd, F_SETFL, 0);
    m=read(fd, buf,1);
    buf[m]=0;
    printf("Initialize: [%s] [X] Desired.\n",buf);
  
    system("/usr/bin/eject /dev/scd0");

    /* Remove CD */
    o = write(fd, "A", 1);
    if (o < 0) fputs("write() of 1 byte failed!\n", stderr);
    fcntl(fd, F_SETFL, 0);
    m=read(fd, buf,1);
    buf[m]=0;
    printf("Remove old: [%s] [X] Desired.\n",buf);
    if( ! buf[0]=='X'){ printf("die!\n"); exit(-1); }

    /* Insert CD */
    o = write(fd, "I", 1);
    if (o < 0) fputs("write() of 1 byte failed!\n", stderr);
    fcntl(fd, F_SETFL, 0);
    m=read(fd, buf,1);
    buf[m]=0;
    printf("Insert new: [%s] [X] Desired.\n",buf);
    if( ! buf[0]=='X'){ printf("die!\n"); exit(-1); }

    system("/usr/bin/eject -t /dev/scd0");

    close(fd);
}
