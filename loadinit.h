#include "control.h"

int loadinit(char *files){
	int n=0;
	int ww1=-1;
	FILE *f1;
	char *enters;
	char c[2080];
	char *aapplication=c;
	f1=fopen(files,"r");
	if(f1==NULL)return -1;
	while(1){
		fgets(c,2070,f1);
		if(feof(f1))break;
		enters=strstr(c,"\n");
		if(enters!=NULL)enters[0]=0;
		enters=strstr(c,"\r");
		if(enters!=NULL)enters[0]=0;
		ww1=newWindow(aapplication,n*20+20,n*20+20,winsw,winsh,100,100,100,aapplication);
		win[n].shms[flagoutput]=-1;
		win[n].shms[flaginput]=-1;
		n++;
	}
	fclose(f1);
	return 0;
}
