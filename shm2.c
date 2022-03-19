#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "dxwindow.h"
int main(int argc,char *argv[]){
	char bufs[2080];
	if (argc<2)exit(0);
	int fd = shm_open(argv[1],O_RDWR ,0);
	if (fd==-1)exit(1);
	if (ftruncate(fd,(winsw*winsh)*(sizeof(int))+50)==-1)exit(1);
	int *shm1=(int*)mmap(NULL,(winsw*winsh)*(sizeof(int))+50,PROT_WRITE | PROT_READ ,MAP_SHARED,fd,0);
	if (shm1!=MAP_FAILED){
		while(1){
			if(shm1[flagend]==1)break;
		}
	}
	puts("exit son");
	shm_unlink(shmp);
	return 0;
}
