all:  serial_drive cd_prev cd_next

serial_drive: serial_drive.c
	gcc -o serial_drive serial_drive.c

cd_prev: cd_prev.c
	gcc -o cd_prev cd_prev.c

cd_next: cd_next.c
	gcc -o cd_next cd_next.c

clean: 
	if [ -f serial_drive ];then rm serial_drive ;fi
	if [ -f cd_prev ];then rm cd_prev ;fi
	if [ -f cd_next ];then rm cd_next ;fi
