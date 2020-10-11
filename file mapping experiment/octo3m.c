#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>
#include <math.h>
#include <complex.h>
#define pi = 3.1415926
struct compx
{
    double re;
    double im;
};
/*void convert(struct compx *a,double i)
{
   struct compx c;
   c.re=cos(i);
   c.im=sin(i);
}*/
void createReadable(char*file){

    int f1,f2;
    char ma[] = "readCmatMap.txt", inte[25];
    f1=open(file,O_RDONLY);
    f2 = open(ma, O_CREAT | O_RDWR | O_TRUNC, 0644);
    struct compx c;
    for (int m = 1; m <= 10; m++)
    {
        for (int n = 1; n <= 10; n++)
        {
            read(f1,&c,sizeof(struct compx));
            sprintf(inte, "%5.3lf+%5.3lfi", c.re, c.im);
            write(f2, inte, strlen(inte));
            if (n == 10 && m != 10)
                write(f2, "\n", 1);
            else if (n != 10)
                write(f2, " ", 1);
        }
    }
    close(f1);
    close(f2);
}
void showStdout(char*file){

    int f1;
    f1=open(file,O_RDONLY);
    struct compx c;
    for (int m = 1; m <= 10; m++)
    {
        for (int n = 1; n <= 10; n++)
        {
            read(f1,&c,sizeof(struct compx));
            printf("%5.3lf+%5.3lfi", c.re, c.im);
            if (n == 10 && m != 10)
              printf("\n");
            else if (n != 10)
               printf(" ");
        }
    }
    close(f1);
}
int main()
{
    int f1,pgSize;
    char ma[] = "Cmatrixmap.txt", inte[25];
    f1 = open(ma, O_CREAT | O_RDWR|O_TRUNC, 0644);
    struct compx c;
    lseek(f1,sizeof(struct compx)*100-1,SEEK_SET);
     write(f1, "", 1);
    lseek(f1, 0, SEEK_SET);
    struct stat sta;
    off_t size;
    struct compx *map;
    sysconf(_SC_PAGE_SIZE);
    fstat(f1,&sta);
    size=sta.st_size;
    map=(struct compx *)mmap(0,size,PROT_WRITE|PROT_READ,MAP_SHARED,f1,0);
    close(f1);
    int q=0;
    for (int m = 1; m <= 10; m++)
    {
        for (int n = 1; n <= 10; n++)
        {
            map[q].re= cos(M_PI/m)+cos(M_PI/n);//(c=e^iπ/m+e^iπ/n)
            map[q].im=sin(M_PI/m)+sin(M_PI/n);
           q++;
        }
    }
  munmap(map,size);
    createReadable(ma);
    showStdout(ma);
}