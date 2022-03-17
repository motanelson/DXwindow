#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "dxwindow.h"
struct shm{
	int sem1;
	int sem2;
	size_t lens;
};
int main(int argc,char *argv[]){
	char shmp[80]="hello1";
	char nolls[80]="";
	char bufs[2080];
	if (argc<2)exit(0);
	int fd = shm_open(argv[1],O_RDWR ,0);
	if (fd==-1)exit(1);
	if (ftruncate(fd,sizeof(struct shm))==-1)exit(1);
	struct shm *shm1=(struct shm*)mmap(NULL,sizeof(*shm1),PROT_WRITE | PROT_READ ,MAP_SHARED,fd,0);
	if (shm1!=MAP_FAILED){
		while(1){
			if(shm1->sem1==1)break;
		}
	}
	puts("exit son");
	shm_unlink(shmp);
	return 0;
}
