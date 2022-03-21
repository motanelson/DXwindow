#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include "control.h"
int *shm1;
char *argvs;
void handler(int value){
	exit(1);
}
void onexits(int i,void *arg){
	printf("on exit %s\n",argvs);
	shm_unlink(argvs);
}
int main(int argc,char *argv[]){
	int i;
	int xx;
	int yy;
	label l1;
	struct windows w1;
	char bufs[2080];
	l1.c.x=25;
	l1.c.y=50;
	l1.c.h=16;
	l1.c.w=45;
	l1.r=100;
	l1.g=100;
	l1.b=100;
	strcpy(l1.caption,"Exit");
	if (argc<2)exit(0);
	argvs=(char*)argv[1];
	signal(SIGINT,handler);
	int fd = shm_open(argv[1],O_RDWR ,0);
	if (fd==-1)exit(1);
	if (ftruncate(fd,(winsw*winsh)*(sizeof(int))+50)==-1)exit(1);
	shm1=(int*)mmap(NULL,(winsw*winsh)*(sizeof(int))+50,PROT_WRITE | PROT_READ ,MAP_SHARED,fd,0);
	if (shm1!=MAP_FAILED){
		on_exit(onexits,(void *)0);
		w1.dc=shm1+shmhead;
		drawLabels(l1,w1.dc);
		shm1[flagoutput]=-1;
		shm1[flagrefresh]=1;
		while(1){
			if(shm1[flagend]==1)break;
			if (shm1[flagoutput]==0){
				xx=shm1[flagoutput+1];
				yy=shm1[flagoutput+2];
				shm1[flagoutput]=-1;
				if(insides(l1,xx,yy)==1){
					shm1[flaginput]=0;
				}

			}

			
		}
	}
	return 0;
}
