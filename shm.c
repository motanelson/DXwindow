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
	char application[80]="./shm2 ";
    char *aapplication=application;
    char *ddhmp=application;
    int i=-1;
    char cc[2080];
    char *ccc;
    int n=0;
	int ii;
	startwin();
	for (n=0;n<4;n++){
		ww1=newWindow(ddhmp,n*20,n*20,winsw,winsh,100,100,100,aapplication);
	}
				if(ww1!=-1){
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
					win[0].shms[flagend]=1;
					win[1].shms[flagend]=1;
					win[2].shms[flagend]=1;
					win[3].shms[flagend]=1;
					sleep(4);
				}
	
	endX(fbfd);
	puts("exit windows gest");
	exitWindow();
	return 0;
}
