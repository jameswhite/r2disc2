#include <stdio.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h> 

char* write_port(char *device_name,char *command,char *buf) {
    struct termios config;
    unsigned short x;
    int fd, n, m, o;
  
    memset(buf, 255, sizeof(char));
    fd = open(device_name, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1){
        fprintf(stderr,"open_port: Unable to open %s", device_name);
    }else{
       if(!isatty(fd)){ 
           fprintf(stderr,"%s is not a tty\n",device_name);
             exit(-1);
        }
        if(tcgetattr(fd, &config) < 0) {
            fprintf(stderr,"unable to read config for %s\n",device_name);
            exit(-1);
        }
        config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
        config.c_oflag = 0;
        config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
        config.c_cflag &= ~(CSIZE | PARENB);
        config.c_cflag |= CS8; // 8n1
        config.c_cc[VMIN]  = 1;
        config.c_cc[VTIME] = 0;
        if(cfsetispeed(&config, B9600) < 0 || cfsetospeed(&config, B9600) < 0) {
            fprintf(stderr,"unable to write config for %s\n",device_name);
            exit(-1);
        }
        if(tcsetattr(fd, TCSAFLUSH, &config) < 0) {
            fprintf(stderr,"unable to apply the config for %s\n",device_name);
            exit(-1);
        }
        fcntl(fd, F_SETFL, 0);
        o = write(fd, command, 1);
        if (o < 0) fputs("write() of 1 byte failed!\n", stderr);
        fcntl(fd, F_SETFL, 0);
        m=read(fd, buf,255);
        buf[m]=0;
        close(fd);
         
    }
    return(buf);
}

void usage(){
    printf("serial_drive <device> <command>\n");
    printf("serial_drive /dev/ttyS0 [C|I|A|G|S|V]\n");
}

int main(int argc, char *argv[]){
    int count=0;
    char buf[255];
    if(argc < 3 || argc >3){
        usage();
        exit(1);
    }
    write_port(argv[1],argv[2],buf);
    printf("%s\n",buf);
    exit (0); 
}
