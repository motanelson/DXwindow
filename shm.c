#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "dxwindow.h"
int main(){
	int ww1=-1;
	char dhmp[80]="hello2";
	char application[80]="./shm2 ";
    char *aapplication=application;
    char *ddhmp=dhmp;
    int i=-1;
    char cc[2080];
    char *ccc;
    int n=0;
	int ii;
	startwin();
		int fd = shm_open(dhmp,O_CREAT | O_EXCL | O_RDWR,S_IRUSR | S_IWUSR);
	if (fd!=-1){
		if (ftruncate(fd,sizeof(struct shm))!=-1){
			struct shm *shm1=(struct shm*)mmap(NULL,sizeof(*shm1),PROT_WRITE | PROT_READ ,MAP_SHARED,fd,0);
			if (shm1!=MAP_FAILED){
				
				ww1=newWindow(ddhmp,20,20,200,200,100,100,100);
				
				if(ww1!=-1){
					shm1->sem1=0;
					shm1->sem2=0;
					runs(aapplication,ddhmp);
					windowsRefresh();
					while(1){
						if(getc(stdin)==27)break;
						i=redrawCursor();
					}
					shm1->sem1=1;
					sleep(4);
				}
			}
		}
	}
	endX(fbfd);
	puts("exit father");
	shm_unlink(dhmp);
	exitWindow();
	return 0;
}
