#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include "dxwindow.h"
void handler(int value){
	exit(1);
}
void onexits(int i,void *arg){
	int n;
	for(n=0;n<wcount;n++){
		if(n<wcount)win[n].shms[flagend]=1;
	}
	sleep(4);
	endX(fbfd);
	puts("exit windows gest");
	exitWindow();
}
int main(){
	int ww1=-1;
	char application[80]="./shm2 ";
    char *aapplication=application;
    char *ddhmp=application;
    int i=-1;
    char cc[2080];
    char *ccc;
    int n=0;
	int ii;
	signal(SIGINT,handler);
	startwin();
	for (n=0;n<4;n++){
		ww1=newWindow(ddhmp,n*20,n*20,winsw,winsh,100,100,100,aapplication);
	}
				if(ww1!=-1){
					on_exit(onexits,(void *)0);
					while(1){
						if(win[0].shms[flagrefresh]==1 && win[1].shms[flagrefresh]==1 && win[2].shms[flagrefresh]==1 && win[3].shms[flagrefresh]==1)break;
					}
					windowsRefresh();
					while(1){
						if(getc(stdin)==27)break;
						i=redrawCursor();
						if(i!=-1){
						moveTop(i);
						windowsRefresh();
					}
	}
				}
	return 0;
}
