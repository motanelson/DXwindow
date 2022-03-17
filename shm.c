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
int main(){
	char shmp[80]="hello1";
	char nolls[80]="---------";
	char runs[80];
    int i=-1;
    char cc[2080];
    char *ccc;
    int n=0;
	int ii;
    int fbfd = startX(nolls);
    if (fbfd == -1) exit(1);
    if ((int)fbp == -1)exit(1);
	int fd = shm_open(shmp,O_CREAT | O_EXCL | O_RDWR,S_IRUSR | S_IWUSR);
	puts("start father");
	if (fd!=-1){
		if (ftruncate(fd,sizeof(struct shm))!=-1){
			struct shm *shm1=(struct shm*)mmap(NULL,sizeof(*shm1),PROT_WRITE | PROT_READ ,MAP_SHARED,fd,0);
			if (shm1!=MAP_FAILED){
				newWindow(ccc,20,20,200,200,100,100,100);
				shm1->sem1=0;
				shm1->sem2=0;
				strcpy(runs,"./shm2 ");
				strcat(runs,shmp);
				strcat(runs," & ");
				system(runs);
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
	exitWindow();
	endX(fbfd);
	puts("exit father");
	shm_unlink(shmp);
	return 0;
}
