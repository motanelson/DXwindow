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
	char caption[80]="Exit";
	char *captions=caption;
	struct windows w1;
	char bufs[2080];
	if (argc<2)exit(0);
	addsControls(25,50,45,16,captions,100,100,100);
	addsControls(80,50,45,16,captions,100,100,100);
	argvs=(char*)argv[1];
	signal(SIGINT,handler);
	int fd = shm_open(argv[1],O_RDWR ,0);
	if (fd==-1)exit(1);
	if (ftruncate(fd,(winsw*winsh)*(sizeof(int))+50)==-1)exit(1);
	shm1=(int*)mmap(NULL,(winsw*winsh)*(sizeof(int))+50,PROT_WRITE | PROT_READ ,MAP_SHARED,fd,0);
	if (shm1!=MAP_FAILED){
		on_exit(onexits,(void *)0);
		w1.dc=shm1+shmhead;
		drawLabelsControls(w1.dc);
		shm1[flagoutput]=-1;
		shm1[flagrefresh]=1;
		while(1){
			if(shm1[flagend]==1)break;
			if (shm1[flagoutput]==0){
				xx=shm1[flagoutput+1];
				yy=shm1[flagoutput+2];
				shm1[flagoutput]=-1;
				if(scanInsides(xx,yy)!=-1){
					shm1[flaginput]=0;
				}

			}

			
		}
	}
	return 0;
}
