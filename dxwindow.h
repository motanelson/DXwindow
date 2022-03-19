#include "directX.h"
#define maxw 32
#define flagend 1
#define winsw 200
#define winsh 200
int fbfd;
#define shmp "XXXIIIXwindows"
struct shm{
	int sem1;
	int sem2;
	size_t lens;
};
struct windows{
	char *title;
	int *dc;
	int x;
	int y;
	int w;
	int h;
	int r;
	int g;
	int b;
	char wc[80];
	int *shms;
};
struct cursors{
	int x;
	int y;
	int x1;
	int y1;
	int *cursor;
	int left;
	int right;
	int middle;
};
int loads=0;
struct cursors curs;
int zorder[maxw];
struct windows win[maxw];
int wcount=0;
void drawlabel(int *dc,char *title,int x,int y,int w, int h){
	char c[w/9+2];
	strncpy(c,title,w/9);
	c[w/9+1]=0;
	igputs(dc,x,y,0,0,0,c);
}
void drawWindow(char *title,int *dc,int x,int y,int w, int h,int r,int g, int b){
	iboxs(0,0,w,h,dc,r,g,b);
	irectangle(0,0,w,h,dc,0,0,0);
	drawlabel(dc,title,0,0,w,h);
}
void runs(char *shells,char *keyss){
		char runs[80];
				runs[0]=0;
				strcat(runs,shells);
				strcat(runs," ");
				strcat(runs,keyss);
				strcat(runs," & ");
				system(runs);
}
int newWindow(char *title,int x,int y,int w, int h,int r,int g, int b,char *aapplication){
	int www=wcount; 	
	if(www<maxw-1){
		win[wcount].title=title;
		win[wcount].x=x;
		win[wcount].y=y;
		win[wcount].w=w;
		win[wcount].h=h;
		win[wcount].r=r;
		win[wcount].g=g;
		win[wcount].b=b;
		if(w>vinfo.xres-1)win[wcount].w=vinfo.xres-1;
		if(w>vinfo.yres-1)win[wcount].h=vinfo.yres-1;
		zorder[wcount]=wcount;
		sprintf(win[wcount].wc,"%s%d",shmp,wcount);
		int fd = shm_open(win[wcount].wc,O_CREAT | O_EXCL | O_RDWR,S_IRUSR | S_IWUSR);
		if (fd==-1)return -1;
		if (ftruncate(fd,(w*h)*(sizeof(int))+50)==-1)return -1;
		win[wcount].shms=(int*)mmap(NULL,(w*h)*(sizeof(int))+50,PROT_WRITE | PROT_READ ,MAP_SHARED,fd,0);
		if (win[wcount].shms==MAP_FAILED)return -1;
		win[wcount].dc=win[wcount].shms+25;
		win[wcount].dc[0]=w;
		win[wcount].dc[1]=h;
		win[wcount].dc[2]=32;
		drawWindow(win[wcount].title,win[wcount].dc,win[wcount].x,win[wcount].y,win[wcount].w,win[wcount].h,win[wcount].r,win[wcount].g,win[wcount].b);
		win[wcount].shms[flagend]=0;
		win[wcount].shms[1]=0;
		runs(aapplication,win[wcount].wc);
		if (www!=-1)wcount++;
	}else{
		www=-1;
	}
	return www;
}
void exitWindow(){
	int n;
	for(n=0;n<wcount;n++){
		if(win[n].dc!=NULL && n<wcount)	shm_unlink(win[n].wc);
	}
	if(curs.cursor!=NULL)free(curs.cursor);
}
void drawCursor(){
	ball(curs.x+16,curs.y+16,3,128,128,128);
	circle(curs.x+16,curs.y+16,3,0,0,0);
}
void showCursor(){
	if (loads==0)curs.cursor=creatImage(32,32);
	loads=1;
	mouseEvent();
	curs.x=mouseX-16;
	curs.y=mouseY-16;
	if(curs.x<0)curs.x=0;
	if(curs.y<0)curs.y=0;
	if(curs.x>=vinfo.xres-1)curs.x=vinfo.xres-33;
	if(curs.y>=vinfo.yres-1)curs.y=vinfo.yres-33;
	curs.x1=curs.x;
	curs.y1=curs.y;
	copyImage(curs.x,curs.y,curs.cursor);
	drawCursor();
}
int onclick(){
	int n;
	int nx;
	int ny;
	int rets=-1;
	for(n=wcount-1;n>0;n--){
		nx=win[zorder[n]].x;
		ny=win[zorder[n]].y;
		if (curs.x1+16>=nx && curs.y1+16>=ny && curs.x1+16<=nx+win[zorder[n]].w && curs.y1+16<=ny+win[zorder[n]].h)return zorder[n];
	}
	return rets;
}
int redrawCursor(){
	int rets=-1;
	int i=-1;
	left=0;
	right=0;
	middle=0;
	i=mouseEvent();
	curs.x1=mouseX-16;
	curs.y1=mouseY-16;
	curs.left=left;
	curs.right=right;
	curs.middle=middle;
	if(curs.x1<0)curs.x1=0;
	if(curs.y1<0)curs.y1=0;
	if(curs.x1>=vinfo.xres-1)curs.x1=vinfo.xres-33;
	if(curs.y1>=vinfo.yres-1)curs.y1=vinfo.yres-33;
	if(curs.x1!=curs.x || curs.y1!=curs.y){
		if(curs.x1!=0 && curs.y1!=0 && curs.x1<vinfo.xres-33 && curs.y1<vinfo.yres-33){
			putImage(curs.x,curs.y,curs.cursor);
			curs.x=curs.x1;
			curs.y=curs.y1;
			copyImage(curs.x,curs.y,curs.cursor);		
			drawCursor();
		}
	}
	if(i==-1 && curs.left!=0)rets=onclick();
	return rets;
}
void windowsRefresh(){
	int n;
	int nx;
	int ny;
	boxs(0,0,vinfo.xres-1,vinfo.yres-1,0,0,0);
	for(n=0;n<wcount;n++){
		nx=win[zorder[n]].x;
		ny=win[zorder[n]].y;
		if(nx+win[zorder[n]].w>vinfo.xres-1)nx=0;
		if(ny+win[zorder[n]].h>vinfo.yres-1)ny=0;
		putImage(nx,ny,win[zorder[n]].dc);
	}
	showCursor();
}
void moveTop(int index){
	int n;
	int i=-1;
	int t=0;
	int o=0;
	for (n=0;n<wcount;n++){
		if(index==zorder[n]){
			t=zorder[n];
			o=1;
		}
		if(o==1){
			zorder[n]=zorder[n+1];
		} 
	}
	zorder[wcount-1]=t;
}
void startwin(){
	char nolls[80]=" ";
    fbfd = startX(nolls);
    if (fbfd == -1) exit(1);
    if ((int)fbp == -1)exit(1);
}

