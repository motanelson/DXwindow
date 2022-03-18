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
    char *ddhmp;
    int i=-1;
    char cc[2080];
    char *ccc;
    int n=0;
	int ii;
	startwin();
	ww1=newWindow(ddhmp,20,20,200,200,100,100,100);
				
				if(ww1!=-1){
					ddhmp=win[0].wc;
					win[0].shms[0]=0;
					win[0].shms[1]=0;
					runs(aapplication,ddhmp);
					windowsRefresh();
					while(1){
						if(getc(stdin)==27)break;
						i=redrawCursor();
					}
					win[0].shms[0]=1;
					sleep(4);
				}
	endX(fbfd);
	puts("exit father");
	exitWindow();
	return 0;
}
